/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 10:21:05 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 03:44:10 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"
#include <stdio.h>

#define SMODE (((t_info *)(node->data))->sbuf->st_mode)
#define SFUB (((t_info *)(node->data))->sbuf)
#define FPATH (((t_info *)(node->data))->fullpath)
#define NAME (((t_info *)(node->data))->name)

void	onedir(char *base, t_args *args);

t_dblist	*newlevel(t_dblist *node, t_args *args)
{
	t_dblist	*hold;

	if ((ft_strcmp("..", NAME)) && ((ft_strcmp(".", NAME))))
	{
		ft_printf("\n%s:\n", FPATH);
		onedir(FPATH, args);
	}
	hold = ft_dblistpop(node);
	singledel(node);
	return (hold);
}

void	subdirdive(t_queue *level, t_args *args)
{
	t_dblist	*node;

	node = level->first;
	while (node)
	{
		if ((SMODE & S_IFDIR) != S_IFDIR)
		{
			if (node == level->first)
			{
				node = singledel(node);
				level->first = node;
			}
			else
				node = singledel(node);
		}
		else
			node = newlevel(node, args);
	}
	free(level);
}

void	multiname(char *str, t_queue *explicit, t_args *args)
{
	t_info		*info;
	char		*new;

	if (!(info = (t_info *)ft_memalloc(sizeof(t_info))))
		exit (0);
	if (!ft_strchr(str, '/') && *str != '.')
	{
		info->name = str;
		new = concatpath(str, "./");
		info->fullpath = new;
		str = new;
	}
	else
		info->fullpath = ft_strdup(str);
	if (setlstat(str, info))
	{
		if (!ft_enqueue(&explicit, (void *)info, sizeof(t_info)))
			exit (0);
	}
	else
	{
		if (str == new)
			free(str);
		args->mul = 1;
		free(info);
	}
}

void	onefile(char *name, t_args *args)
{
	char	*start;

	start = ft_strchr(name, '/');
	if (start)
		start++;
	else
		return ;
	ft_printf("%s\n", start);
	args = 0;
}

#define IFPATH (info->fullpath)
#define INAME (info->name)

t_queue		*buildir(DIR *d_base, char *base)
{
	t_info	*info;
	t_queue	*level;
	char	*new;

	if (!(info = (t_info *)ft_memalloc(sizeof(t_info)))
		|| !((level = (t_queue *)ft_memalloc(sizeof(t_queue)))))
		exit (0);
	while ((info->entry = readdir(d_base)))
	{
		info->name = ft_strdup(info->entry->d_name);
		IFPATH = concatpath("/", base);
		new = concatpath(INAME, IFPATH);
		free(IFPATH);
		IFPATH = new;
		if (setlstat(IFPATH, info))
		{
			if (!(ft_enqueue(&level, info, sizeof(t_info)))
				|| !(info = (t_info *)ft_memalloc(sizeof(t_info))))
				exit (0);
		}
		else
		{
			free(INAME);
			free(IFPATH);
		}
	}
	free(info);
	return (level);
}

void	onedir(char *base, t_args *args)
{
	DIR		*d_base;
	t_queue	*level;		

	if (!(d_base = opendir(base)))
	{
		ft_printf("ftls: %s: %s\n", base, strerror(errno));
		return ;
	}
	level = buildir(d_base, base);
	closedir(d_base);
	level->first = ft_mergesort(level->first, &lexosort);
	ft_queue_postsort(level);
	if (!args->a)
		pophidden(level);
	printlevel(level, args);
	if (args->R && level->first)
	{
		pophidden(level);
		subdirdive(level, args);
	}
	else
		ft_queue_destruc(level, &singledel);
}

void	buildlevels(t_queue *explicit, t_args *args)
{
	t_dblist	*node;
	t_dblist	*hold;

	node = explicit->first;
	while (node)
	{
		if (args->mul)
			ft_printf("\n%s:\n", FPATH);
		onedir(FPATH, args);
		hold = ft_dblistpop(node);
		singledel(node);
		node = hold;
		args->mul = 1;
		if (node)
			ft_printf("\n");
	}
}

void	expfiles(t_queue *explicit, t_args *args)
{
	t_dblist	*node;
//	t_dblist	*hold;

	node = explicit->first;
	while (node)
	{
		if ((SMODE & S_IFDIR) != S_IFDIR)
		{
			onefile(FPATH, args);
			args->mul = 1;
			if (node == explicit->first)
			{
				node = singledelargv(node);
				explicit->first = node;
//				ft_popfront(explicit);
//				node = singledelargv(node);
			}
			else
			{
//				hold = ft_dblistpop(node);
//				singledelargv(node);
//				node = hold;
				singledelargv(node);
				node = node->next;
			}
		}
		else
			node = node->next;
	}
}

void	findexp(char **argv, t_args *args)
{
	t_queue		*explicit;

	parseflags(&argv, args);
	if (!(explicit = (t_queue *)ft_memalloc(sizeof(t_queue))))
		exit (0);
	if (!(*argv))
		onedir(".", args);
	while (*argv)
		multiname(*argv++, explicit, args);
	if (explicit->first)
		explicit->first = ft_mergesort(explicit->first, &lexosort);
	else
	{
		free(explicit);
		exit (0);
	}
	ft_queue_postsort(explicit);
	expfiles(explicit, args);
	buildlevels(explicit, args);
}

int		main(int argc, char **argv)
{
	t_args	args;

	if (argc == 1)
		onedir(".", &args);
	else
		findexp(++argv, &args);
}

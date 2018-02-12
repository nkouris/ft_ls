/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accruedata.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 04:03:53 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 04:07:48 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"
#include <stdio.h>

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

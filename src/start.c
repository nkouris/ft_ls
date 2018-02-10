/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:00:18 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/09 20:00:19 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		subdir_dive(t_lsnode *top, t_lssort *args)
{
	t_lsnode	*temp;

	temp = top;
	while (top)
	{
		if ((ft_strcmp(temp->name, "..") > 0) && temp->perms[0] == 'd')
		{
			ft_printf("is hidden? %d\n", ft_strcmp(temp->name, ".."));
			clean_level(&top, &temp, args);
			break ;
		}
		else
			temp = temp->next;
		if (!temp)
			top = 0;
	}
	if (temp)
	{
		if (!args->exp)
			ft_printf("\n%s:\n", temp->dirstr);
		args->exp = 0;
		print_directories(temp, args);
	}
	if (top)
		subdir_dive(top, args);
}

static void	print_listdir(t_lsnode *top, t_lssort *args)
{
	t_lsnode	*temp;
	int			blocks;

	blocks = 0;
	temp = top;
	while (temp)
	{
		blocks = blocks + temp->sbuf->st_blocks;
		temp = temp->next;
	}
	temp = top;
	while (temp)
	{
		if (!temp->solo)
		{
			ft_printf("total %d\n", blocks);
			blocks = 0;
		}
		while (temp)
		{
			ft_printf("%-12s%-*d%-*s%-*s%*d %.12s %s", temp->perms,
			args->m_nlink + 1, temp->sbuf->st_nlink,
			sizeof(temp->pass->pw_name) + 1, temp->pass->pw_name,
			sizeof(temp->group->gr_name), temp->group->gr_name,
			args->m_bytelen, temp->sbuf->st_size, &(temp->time[4]), temp->name);
			if (temp->link)
				ft_printf(" -> %s", temp->link);
			ft_printf("\n");
			temp = temp->next;
		}
	}
	if (args->R)
		subdir_dive(top, args);
}

void		print_directories(t_lsnode *top, t_lssort *args)
{
	t_lsnode	*temp;

	temp = top;
	if (args->l)
		print_listdir(top, args);
	else
	{
		ft_printf("Start p\n");
		while (temp)
		{
			ft_printf("%s\n", temp->name);
			temp = temp->next;
		}
		ft_printf("\n");
	}
	if (args->R && !args->l)
	{
		ft_printf("recurse\n");
		subdir_dive(top, args);
	}
}

void	current_dir(t_lsnode **top, t_lssort *args, char *fname)
{
	t_lsnode 		*new;
	struct dirent 	*element;


	ft_printf("\nname: %s\ntopdir= %p\n", fname, (*top)->dir);
	if (!((*top)->dir = opendir(fname)))
	{
		ft_printf("%s", strerror(errno));
		exit(0);
	}
	ft_printf("\nname: %s\ntopdir= %p\n", fname, (*top)->dir);
	while ((element = readdir((*top)->dir)))
	{
		if (!(*top)->name)
		{
			fill_node((*top), (*top), fname, element);
			fieldwidth_match(args, (*top));
			(*top)->dirstr = fname;
		}
		else
		{
			new = create_node(element, (*top), fname);
			new->dirstr = fname;
			push_level(new, top, args);
		}
	}
	closedir((*top)->dir);
	if (!args->a)
		rmhidden(top);
}

void	create_level(t_lsnode **top, t_lssort *args, char **argv)
{
	int			i;
	t_lsnode	*hold;

	i = 0;
	if (!argv)
		current_dir(top, args, ".");
	else
	{
		while (*argv)
			i += explicit(top, args, *argv++);
		while ((*top) && i)
		{
			hold = (*top)->next;
			(*top)->next = 0;
			if ((*top)->perms[0] == 'd')
				subdir_dive((*top), args);
			else
				print_directories((*top), args);
			args->exp = 0;
			(*top) = hold;
		}
	}
}

int		main(int argc, char **argv)
{
	t_lsnode		*top;
	t_lssort		*args;
	int				i;

	if (!(top = (t_lsnode *)ft_memalloc(sizeof(t_lsnode))) 
		|| !(args = (t_lssort *)ft_memalloc(sizeof(t_lssort))))
		return (1);
	argc > 1 ? (i = check_args(&argv, &args)) : (i = 0);
	if ((i && argc == 2) || argc == 1)
		argv = 0;
	create_level(&top, args, argv);
	if (!args->exp)
	{
		ft_printf("yo\n");
		print_directories(top, args);
	}
//	if (top->dir)
//	closedir(top->dir);
//	cleanup(top);
	return(0);
}

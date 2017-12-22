/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:00:18 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/21 19:18:10 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		subdir_dive(t_lsnode *top, t_lssort *args)
{
	t_lsnode	*temp;

	temp = top;
	while (temp)
	{
		if (temp->perms[0] == 'd')
		{
			clean_level(&top, &temp, args);
			break ;
		}
		else
			temp = temp->next;
	}
	if (temp)
	{
		ft_printf("\n%s:\n", temp->fullpath);
		print_directories(temp, args);
	}
	if (top)
		print_directories(top, args);
}

static void	print_listdir(t_lsnode *top, t_lssort *args)
{
	t_lsnode	*temp;
	int			blocks;

	blocks = 0;
	if (!args->a)
		rmhidden(&top);
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
			ft_printf("%-12s%-*d%-*s%-*s %*d %.12s %s\n", temp->perms,
			temp->m_nlink + 1, temp->sbuf->st_nlink,
			sizeof(temp->pass->pw_name) + 1, temp->pass->pw_name,
			sizeof(temp->group->gr_name), temp->group->gr_name,
			temp->m_bytelen, temp->sbuf->st_size, &(temp->time[4]), temp->name);
			temp = temp->next;
		}
	}
	if (args->R && !args->exp)
		subdir_dive(top, args);
}

void		print_directories(t_lsnode *top, t_lssort *args)
{
	int			pad;
	t_lsnode	*temp;

	if (args->l)
		print_listdir(top, args);
	else
	{
		if (!args->a)
			rmhidden(&top);
		temp = top;
		while (temp)
		{
			pad = 8 + temp->namelen;
			ft_printf("%-*s", pad, temp->name);
			temp = temp->next;
		}
	}
	if (args->R && !args->exp)
		subdir_dive(top, args);
}

/*---------------------------------------------------------- OLD OLD OLD OLD OLD

static int	store_current_dir(t_lsnode **top, t_lssort *args, char *str)
{
	t_lsnode		*node;
	struct dirent	*element;

	node = 0;
	element = 0;
	// Statement runs the provided str argument through opendir, which will
	// fail if the provided str is not a vaild path.

	// ***  Solocheck will only fire when explicit files are listed from the 
	// 		current directory, thereby appending "./" to the str argument! ***
	if (!((*top)->dir = opendir(str)))
	{
		if (!solo_check(top, str, args))
		{
			ft_printf("ls: %s: No such file or directory\n", str);
			return (0);
		}
		else
			return (1);
	}
	while ((element = readdir((*top)->dir)))
	{
		if (!(*top)->name)
			(*top) = create_node(element, (*top), str);
		else
		{
			node = create_node(element, (*top), str);
			node->dirstr = str;
			push_node(node, top, args);
		}
	}
	return (1);
}

OLD OLD OLD OLD OLD ----------------------------------------------------------*/

void	current_dir(t_lsnode **top, t_lssort *args, char *fname)
{
	t_lsnode 		*new;
	struct dirent 	*element;

	(*top)->dir = opendir(fname);
	while ((element = readdir((*top)->dir)))
	{
		if (!(*top)->name)
			(*top) = create_node(element, (*top), fname);
		else
		{
			new = create_node(element, (*top), fname);
			new->dirstr = fname;
			push_level(new, top, args);
		}
	}
}

/*---------------------------------------------------------- OLD OLD OLD OLD OLD

static void	store_directories(t_lsnode **top, t_lssort *args, char **argv)
{
	// Base case that fires if there are no explicit arguments, or only a
	// parameter was set, meaning that the program is being run on the current
	// folder.
	if (!argv)
		store_current_dir(top, args, ".");
	else
	{
		while (*argv)
			store_current_dir(top, args, *argv++);
	}
}

OLD OLD OLD OLD OLD ----------------------------------------------------------*/

void	create_level(t_lsnode **top, t_lssort *args, char **argv)
{
	if (!argv)
		current_dir(top, args, ".");
	else
	{
		while (**argv)
			explicit(top, args, *argv);
	}
}

int		main(int argc, char **argv)
{
	t_lsnode		*top;
	t_lssort		*args;
	int				i;

	if (!(top = create_node(0, 0, 0)) 
		|| !(args = (t_lssort *)ft_memalloc(sizeof(t_lssort))))
		return (1);
	argc > 1 ? (i = check_args(&argv, &args)) : (i = 0);
	if ((i && argc == 2) || argc == 1)
		argv = 0;
	create_level(&top, args, argv);
	print_directories(top, args);
	if (top->dir)
		closedir(top->dir);
	cleanup(top);
	return(0);
}

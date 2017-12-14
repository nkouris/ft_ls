/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:00:18 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/13 17:57:01 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_directories(t_lsnode **root)
{
	int		pad;
	int		i;

	i = 0;
	while (*root)
	{
		if (i)
			pad = 10;
		else
			pad = 0;
		ft_printf("%*s", pad, (*root)->name);
		root = &((*root)->next);
		i++;
	}
}

static void	store_current_dir(t_lsnode **root, t_lssort **args, char *str)
{
	t_lsnode		*new;
	struct dirent	*element;

	new = 0;
	element = 0;
	if (!((*root)->dir = opendir(str)))
		exit (1);
	while ((element = readdir((*root)->dir)))
	{
		if (!(*root)->namelen)
			(*root) = create_node(element, (*root)->dir);
		else
		{
			new = create_node(element, (*root)->dir);
			push_node(new, root, args);
		}
	}
}

static void	store_explicit_dir(t_lsnode **root, t_lssort **args, char **argv)
{
	while (*argv)
		store_current_dir(root, args, *argv++);
}


static void	store_directories(t_lsnode **root, t_lssort **args, char **argv)
{
	if (!argv)
		store_current_dir(root, args, ".");
	else
		store_explicit_dir(root, args, argv);
}

int		main(int argc, char **argv)
{
	// init data structures
	t_lsnode		*root;
	t_lssort		*args;

	if (!(root = create_node(0, 0)) 
		|| !(args = create_args()))
		return (1);
	
	if (argc > 1)
	{
		parse_args(&argv, &args);
		argv++;
	}
	else
		argv = 0;
/*	printf("l: %d\n", args->l);
	printf("R: %d\n", args->R);
	printf("a: %d\n", args->a);
	printf("r: %d\n", args->r);
	printf("t: %d\n", args->t);*/
	store_directories(&root, &args, argv);
	print_directories(&root);
	return(0);
}

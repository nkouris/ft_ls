/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:00:18 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/12 17:35:04 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/*
static void	store_explicit_dir(t_lsleaf *root, t_sort *args, char **argv)
{
	while (*++argv)
		store_current_dir(root, args, *argv);
}

static void	store_current_dir(t_lsleaf *root, t_lssort *args, char *str)
{
	t_lsleaf		*top;
	t_lsleaf		*new;
	struct dirent	*element;

	top = 0;
	new = 0;
	element = 0;
	if (!(root->dir = opendir(str)))
		exit (1);
	while (element = readdir(root->dir))
	{
		if (!top)
			top = create_leaf(element);
		else
		{
			new = create_leaf(element);
			push_leaf(new, top);
		}
	}
}

static void	store_directories(t_lsleaf **root, t_lssort **args, char **argv);
{
	if (!argv)
		store_current_dir(root, criteria, ".");
	else
		store_explicit_dir(root, criteria, argv);
}
*/
int		main(int argc, char **argv)
{
	// init data structures
	t_lsleaf		*root;
	t_lssort		*args;

	if (!(root = create_leaf(0)) 
		|| !(args = create_args()))
		return (1);
	
	if (argc > 1)
	{
		parse_args(&argv, &args);
		argv++;
	}
	else
		argv = 0;
	printf("l: %d\n", args->l);
	printf("R: %d\n", args->R);
	printf("a: %d\n", args->a);
	printf("r: %d\n", args->r);
	printf("t: %d\n", args->t);
/*	store_directories(&root, criteria, argv);
	print_directories(&root);*/
	return(0);
}

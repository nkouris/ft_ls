/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:00:18 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/15 20:26:59 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_ldirectories(t_lsnode *root)
{
	t_lsnode	*temp;
	int			blocks;

	temp = root;
	blocks = 0;
	while (temp)
	{
		blocks = blocks + temp->sbuf->st_blocks;
		temp = temp->next;
	}
	ft_printf("total %d\n", blocks);
	while (root)
	{
		ft_printf("%-12s%-*d%s\n", root->perms, (sizeof(root->namelen) / 4) + 1,
		root->sbuf->st_nlink, root->name);
		root = root->next;
	}
}

static void	print_directories(t_lsnode *root, t_lssort *args)
{
	int		pad;
	int		i;

	i = 0;
	if (args->l)
		print_ldirectories(root);
	else
	{
		while (root)
		{
			if (i)
				pad = root->namelen + 4;
			else
				pad = 0;
			ft_printf("%*s", pad, root->name);
			root = root->next;
			i++;
		}
	}
}

static void	store_current_dir(t_lsnode **root, t_lssort *args, char *str)
{
	t_lsnode		*node;
	struct dirent	*element;

	node = 0;
	element = 0;
	if (!((*root)->dir = opendir(str)))
		exit (1);
	while ((element = readdir((*root)->dir)))
	{
		if (!(*root)->namelen)
			(*root) = create_node(element, (*root)->dir);
		else
		{
			node = create_node(element, (*root)->dir);
			push_node(node, root, args);
		}
	}
}

static void	store_directories(t_lsnode **root, t_lssort *args, char **argv)
{
	if (!argv)
		store_current_dir(root, args, ".");
	else
	{
		while (*argv)
			store_current_dir(root, args, *argv++);
	}
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
		parse_args(&argv, args);
		args ? argv = 0 : argv++;
	}
	else
		argv = 0;
	store_directories(&root, args, argv);
	argsact(args, &root);
	print_directories(root, args);
	closedir(root->dir);
	cleanup(root);
	return(0);
}

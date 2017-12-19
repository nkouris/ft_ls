/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:00:18 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/18 22:12:29 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_listdir(t_lsnode *root)
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
	while (root)
	{
		if (root->multi && root->dirstr)
			ft_printf("\n%s:\n", root->dirstr);
		if (!root->solo)
		{
			ft_printf("total %d\n", blocks);
			blocks = 0;
		}
		while (root)
		{
			ft_printf("%-12s%-*d%-*s%-*s %*d %12s %s\n", root->perms,
			root->m_nlink + 1, root->sbuf->st_nlink,
			sizeof(root->pass->pw_name) + 1, root->pass->pw_name,
			sizeof(root->group->gr_name), root->group->gr_name,
			root->m_bytelen, root->sbuf->st_size, &(root->time[4]), root->name);
			root = root->next;
			if (root)
			{
				if (!root->solo && blocks)
					break ;
			}
		}
	}
}

void		print_directories(t_lsnode *root, t_lssort *args)
{
	int		pad;
	int		i;

	i = 0;
	if (args->l)
		print_listdir(root);
	else
	{
	//	print_blockdir(root);
		while (root && root->name)
		{
			if (i)
				pad = sizeof(root->name) + 4;
			else
				pad = 0;
			ft_printf("%*s", pad, root->name);
			root = root->next;
			i++;
		}
		ft_printf("\n");
	}
}

static int	store_current_dir(t_lsnode **root, t_lssort *args, char *str)
{
	t_lsnode		*node;
	struct dirent	*element;

	node = 0;
	element = 0;
	if (!((*root)->dir = opendir(str)))
	{
		if (!solo_check(root, str, args))
		{
			ft_printf("ls: %s: No such file or directory\n", str);
			return (0);
		}
		else
			return (1);
	}
	while ((element = readdir((*root)->dir)))
	{
		if (!(*root)->name)
			(*root) = create_node(element, (*root)->dir, str, (*root)->multi);
		else
		{
			node = create_node(element, (*root)->dir, str, (*root)->multi);
			node->dirstr = str;
			push_node(node, root, args);
		}
	}
	return (1);
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

	if (!(root = create_node(0, 0, 0, 0)) 
		|| !(args = create_args()))
		return (1);
	if (argc > 1)
	{
		check_args(&argv, &args);
		if (argc > 2)
			root->multi = 1;
		args && argc == 2 ? argv = 0 : argv;
	}
	else
		argv = 0;
	store_directories(&root, args, argv);
	argsact(args, &root);
	print_directories(root, args);
	if (root->dir)
		closedir(root->dir);
	cleanup(root);
	return(0);
}

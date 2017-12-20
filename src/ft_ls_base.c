/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:00:18 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/19 20:07:54 by nkouris          ###   ########.fr       */
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
			ft_printf("%-12s%-*d%-*s%-*s %*d %.12s %s\n", root->perms,
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

	if (args->l)
		print_listdir(root);
	else
	{
	//	print_blockdir(root);
		while (root && root->name)
		{
			pad = '\t' + sizeof(root->name);
			ft_printf("%-*s", pad, root->name);
			root = root->next;
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
	// Statement runs the provided str argument through opendir, which will
	// fail if the provided str is not a vaild path.

	// ***  Solocheck will only fire when explicit files are listed from the 
	// 		current directory, thereby appending "./" to the str argument! ***
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
			(*root) = create_node(element, (*root), str);
		else
		{
			node = create_node(element, (*root), str);
			node->dirstr = str;
			push_node(node, root, args);
		}
	}
	return (1);
}

static void	store_directories(t_lsnode **root, t_lssort *args, char **argv)
{
	// Base case that fires if there are no explicit arguments, or only a
	// parameter was set, meaning that the program is being run on the current
	// folder.
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

	if (!(root = create_node(0, 0, 0)) 
		|| !(args = (t_lssort *)ft_memalloc(sizeof(t_lssort))))
		return (1);
	// Multiple argument handling, if there is no parameter, check args returns
	// 0 and argv is not set to null, allowing a single explicit file ls
	if (argc > 1)
	{
		if (argc > 2)
			root->multi = 1;
		if (check_args(&argv, &args) && argc == 2)
			argv = 0;
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

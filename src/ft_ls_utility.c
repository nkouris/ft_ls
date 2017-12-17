/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:58:50 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/16 16:05:24 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_numlen(int num)
{
	int i;

	i = 0;
	if (num == -2147483648)
		return (10);
	if (num < 0)
		num = num * -1;
	while (num)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

static void	rmhidden(t_lsnode **root)
{
	t_lsnode *front;
	t_lsnode *back;

	front = (*root);
	while ((*root)->name[0] == '.')
	{
		(*root) = (*root)->next;
		ft_memdel((void **)&front);
		front = (*root);
	}
	while (front)
	{
		while (front->name[0] == '.')
		{
			back->next = front->next;
			ft_memdel((void **)&front);
			if (back->next)
				front = back->next;
			else
				break ;
		}
		back = front;
		front ? front = front->next : front;
	}
}

void		argsact(t_lssort *args, t_lsnode **root)
{
	if (!args || !args->a)
		rmhidden(root);
}

void		cleanup(t_lsnode *root)
{
	t_lsnode	*hold;

	while (root)
	{
		hold = root->next;
		ft_memdel((void **)&root);	
		root = hold;
	}
}

#define SNODE node->sbuf->st_mode

void		cat_files(t_lsnode *node)
{
	if ((SNODE & S_IFDIR) == S_IFDIR)
		node->perms[0] = 'd';
	if ((SNODE & S_IRUSR) == S_IRUSR)
		node->perms[1] = 'r';
	if ((SNODE & S_IWUSR) == S_IWUSR)
		node->perms[2] = 'w';
	if ((SNODE & S_IXUSR) == S_IXUSR)
		node->perms[3] = 'x';
	if ((SNODE & S_IRGRP) == S_IRGRP)
		node->perms[4] = 'r';
	if ((SNODE & S_IWGRP) == S_IWGRP)
		node->perms[5] = 'w';
	if ((SNODE & S_IXGRP) == S_IXGRP)
		node->perms[6] = 'x';
	if ((SNODE & S_IROTH) == S_IROTH)
		node->perms[7] = 'r';
	if ((SNODE & S_IWOTH) == S_IWOTH)
		node->perms[8] = 'w';
	if ((SNODE & S_IXOTH) == S_IXOTH)
		node->perms[9] = 'x';
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_explicit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 19:53:05 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/20 12:21:02 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		solo_check(t_lsnode **root, char *str, t_lssort *args)
{
	t_lsnode	*node;
	struct stat	*sbuf;

	if (!(node = ft_memalloc(sizeof(t_lsnode)))
		|| !(sbuf = (struct stat *)ft_memalloc(sizeof(struct stat))))
		return (0);
	node->name = str;
	node->sbuf = sbuf;
	if ((lstat((const char *)node->name, sbuf)) < 0)
	{
		node->fullpath = strfpath(node, ".");
		if ((lstat((const char *)node->fullpath, sbuf)) < 0)
			return (0);
	}
	ft_memset(node->perms, '-', 10);
	node->solo = 1;
	node->multi = (*root)->multi;
	use_stats(node);
	cat_files(node);
	if (!(*root)->name)
		(*root) = node;
	else
		solo_push_node(node, root, args);
	return (1);
}

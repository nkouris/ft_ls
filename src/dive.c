/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dive.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 03:58:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 04:26:22 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"
#include <stdio.h>

t_dblist	*newlevel(t_dblist *node, t_args *args)
{
	t_dblist	*hold;

	if ((ft_strcmp("..", NAME)) && ((ft_strcmp(".", NAME))))
	{
		ft_printf("\n%s:\n", FPATH);
		onedir(FPATH, args);
	}
	hold = ft_dblistpop(node);
	singledel(node);
	return (hold);
}

void		subdirdive(t_queue *level, t_args *args)
{
	t_dblist	*node;

	node = level->first;
	while (node)
	{
		if ((SMODE & S_IFDIR) != S_IFDIR)
		{
			if (node == level->first)
			{
				node = singledel(node);
				level->first = node;
			}
			else
				node = singledel(node);
		}
		else
			node = newlevel(node, args);
	}
	free(level);
}

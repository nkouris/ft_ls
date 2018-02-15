/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:40:17 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/14 17:22:08 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

static void	l_printlevel(t_queue *level, t_args *args)
{
	t_dblist		*node;
	char			*perm;
	int				total;
	struct s_width	width;
	
	node = level->first;
	perm = ft_strnew(10);
	ft_memset(perm, '-', 10);
	ft_memset(&width, 0, sizeof(t_width));
	while (node)
	{
		total = BLOCK + total;
		widthcalc(node, &width);
		node = node->next;
	}
	args->r ? (node = level->last) : (node = level->first);
	ft_printf("total %d\n", (total - 1));
	while (node)
	{
		getperms(&perm, node, args);
		ft_printf("%-12s%-*d%-*s%-*s", perm, width.col1 + 1, LINKS,
					width.col2 + 2, USER, width.col3 + 2, GROUP);
		if (args->links)
		{
			ft_printf("%*d,%*d% 17.16s %-s\n", width.devmaj + 1, MAJOR,
					width.devmin + 1, MINOR, TIME, NAME);
		}
		else
			ft_printf("%-*d% 17.16s %-s\n", width.col4 + 1, BYTES, TIME, NAME);
		perm = (char *)ft_memset(perm, '-', 10);
		args->r ? (node = node->prec) : (node = node->next);
	}
	free(perm);
}

void	printlevel(t_queue *level, t_args *args)
{
	t_dblist	*node;

	if (args->l)
	{
		l_printlevel(level, args);
		return ;
	}
	args->r ? (node = level->last) : (node = level->first);
	while (node)
	{
		ft_printf("%s\n", NAME);
		args->r ? (node = node->prec) : (node = node->next);
	}
}

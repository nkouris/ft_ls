/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:40:17 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 04:12:20 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

#define NAME (((t_info *)(node->data))->name)

void	printlevel(t_queue *level, t_args *args)
{
	t_dblist	*node;

	if (args->r)
	{
		node = level->last;
		while (node)
		{
			ft_printf("%s\n", NAME);
			node = node->prec;
		}
		return ;
	}
	else
	{
		node = level->first;
		while (node)
		{
			if (NAME == "\n")
				;
			else
				ft_printf("%s\n", NAME);
			node = node->next;
		}
		return ;
	}
}

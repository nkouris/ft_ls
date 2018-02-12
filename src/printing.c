/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:40:17 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 01:00:41 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

#define NAME (((t_info *)(temp->data))->name)

void	printlevel(t_queue *level, t_args *args)
{
	t_dblist	*temp;

	if (args->r)
	{
		temp = level->last;
		while (temp)
		{
			ft_printf("%s\n", NAME);
			temp = temp->prec;
		}
		return ;
	}
	else
	{
		temp = level->first;
		while (temp)
		{
			if (NAME == "\n")
				;
			else
				ft_printf("%s\n", NAME);
			temp = temp->next;
		}
		return ;
	}
}

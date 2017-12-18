/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_listhandling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:20:22 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/17 16:33:34 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	if ((!args || !args->a) && (*root)->name)
		rmhidden(root);
/* Build our sorting options */
}

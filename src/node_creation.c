/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:06:10 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/21 19:03:16 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		asort(t_lsnode **top, t_lsnode *new)
{
	t_lsnode *front;
	t_lsnode *back;
	
	front = (*top);
	if (ft_strcmp((const char *)new->name, (const char *)(*top)->name) > 0)
	{
		 new->next = front;
		 (*top) = new;
	}
	else
	{
		while (ft_strcmp((const char *)front->name,(const char *)new->name) < 0)
		{
			back = front;
			front = front->next;
		}
		if (front)
		{
			back->next = new;
			new->next = front;
		}
		else
			front->next = new;
	}
}

#define TSPEC st_mtimespec.tv_sec

void		tsort(t_lsnode **top, t_lsnode *new)
{
	t_lsnode *front;
	t_lsnode *back;
	
	front = (*top);
	if (new->sbuf->TSPEC < (*top)->sbuf->TSPEC)
	{
		 new->next = front;
		 (*top) = new;
	}
	else
	{
		while (front->sbuf->TSPEC > new->sbuf->TSPEC)
		{
			back = front;
			front = front->next;
		}
		if (front)
		{
			back->next = new;
			new->next = front;
		}
		else
			front->next = new;
	}
}

void		push_level(t_lsnode *new, t_lsnode **top, t_lssort *args)
{
	fieldwidth_match(*top, new);
	if (args->t)
		tsort(top, new);
	asort(top, new);
}

t_lsnode	*create_node(struct dirent *element, t_lsnode *root, char *str)
{
	t_lsnode	*node;

	if (!(node = (t_lsnode *)ft_memalloc(sizeof(t_lsnode))))
		exit (1);
	if (element)
		fill_node(node, root, str, element);
	return (node);
}

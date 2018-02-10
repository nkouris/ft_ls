/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:06:10 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/09 17:22:02 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		asort_dive(t_lsnode **top, t_lsnode *new)
{
	t_lsnode 	*front;
	t_lsnode 	*back;
	int			i;

	front = (*top);
	i = 0;
	while (ft_strcmp((const char *)front->name,(const char *)new->name) < 0)
	{
		back = front;
		if (front->next)
			front = front->next;
		else
		{
			i = 1;
			break ;
		}
	}
	if (!i)
	{
		back->next = new;
		new->next = front;
	}
	else
		front->next = new;
}

void		asort(t_lsnode **top, t_lsnode *new)
{
	t_lsnode *front;
	
	front = (*top);
	if (ft_strcmp((const char *)new->name, (const char *)(*top)->name) < 0)
	{
		 new->next = front;
		 (*top) = new;
	}
	else
		asort_dive(top, new);
}

#define TSPEC st_mtimespec.tv_sec
#define NTSPEC st_mtimespec.tv_nsec

void		tsort_dive(t_lsnode **top, t_lsnode *new)
{
	t_lsnode 	*front;
	t_lsnode 	*back;
	int			i;

	front = (*top);
	i = 0;
	while (front->sbuf->TSPEC >= new->sbuf->TSPEC)
	{
		back = front;
		if (front->next)
			front = front->next;
		else
		{
			i = 1;
			break ;
		}
	}
	if (!i)
	{
		back->next = new;
		new->next = front;
	}
	else
		front->next = new;

}

void		tsort(t_lsnode **top, t_lsnode *new)
{
	t_lsnode *front;
	
	front = (*top);
	if ((new->sbuf->TSPEC > (*top)->sbuf->TSPEC)
		|| ((new->sbuf->TSPEC == (*top)->sbuf->TSPEC)
			&& (new->sbuf->NTSPEC > (*top)->sbuf->NTSPEC)))
	{
		 new->next = front;
		 (*top) = new;
	}
	else
		tsort_dive(top, new);
}

void		push_level(t_lsnode *new, t_lsnode **top, t_lssort *args)
{
	fieldwidth_match(args, new);
	if (args->t)
		tsort(top, new);
	else
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

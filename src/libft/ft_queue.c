/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:33:00 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 02:58:35 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**		Using a doubly linked list, as defined in libft.h
**				|
**				first -> (next)
**				(next)
**				.
**				.
**				.
**				.
**				.
**				(prec)
**				last -> (prec)
**				|
*/

int			ft_enqueue(t_queue **key, void *data, size_t size)
{
	t_dblist	*add;

	if (!(add = ft_dblistnew(data, size)))
		return (0);
	if (!(*key)->first)
		ft_pushfront(*key, add);
	else
		ft_pushend(*key, add);
	return (1);
}

void		ft_pushfront(t_queue *key, t_dblist *data)
{
	t_dblist	*temp;

	if (key)
	{
		key->qlen++;
		if (!key->first)
		{
			key->first = data;
			key->last = data;
		}
		else
		{
			temp = key->first;
			data->next = temp;
			data->prec = 0;
			temp->prec = data;
			key->first = data;
		}
	}
}

void		ft_pushend(t_queue *key, t_dblist *data)
{
	t_dblist	*temp;

	if (key)
	{
		key->qlen++;
		if (!key->last)
		{
			key->last = data;
			data->prec = key->first;
			key->first->next = data;
		}
		else
		{
			temp = key->last;
			data->prec = temp;
			data->next = 0;
			temp->next = data;
			key->last = data;
		}
	}
}

t_dblist	*ft_popfront(t_queue *key)
{
	t_dblist	*temp;

	if (!key)
		return (0);
	else
	{
		if (key->first)
		{
			key->qlen ? key->qlen-- : key->qlen;
			temp = key->first;
			key->first = key->first->next;
			key->first ? key->first->prec = 0 : key->first;
			temp->next = 0;
			return (temp);
		}
	}
	return (0);
}

t_dblist	*ft_popend(t_queue *key)
{
	t_dblist	*temp;

	if (!key)
		return (0);
	else
	{
		if (key->last)
		{
			key->qlen ? key->qlen-- : key->qlen;
			temp = key->last;
			key->last = key->last->prec;
			key->last ? key->last->next = 0 : key->last;
			temp->prec = 0;
			return (temp);
		}
	}
	return (0);
}

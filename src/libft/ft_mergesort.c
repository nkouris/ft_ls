/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 22:53:47 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 02:55:04 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist		*splithalf(t_dblist *head)
{
	t_dblist	*high;
	t_dblist	*low;
	t_dblist	*temp;

	high = head;
	low = head;
	while (low->next && low->next->next)
	{
		low = low->next->next;
		high = high->next;
	}
	temp = high->next;
	high->next = 0;
	return (temp);
}

t_dblist		*listmerge(t_dblist *one, t_dblist *two,
				int (*f)(void *, void *))
{
	if (!one)
		return (two);
	if (!two)
		return (one);
	if (f(one->data, two->data) == 1)
	{
		one->next = listmerge(one->next, two, f);
		one->next->prec = one;
		one->prec = 0;
		return (one);
	}
	else
	{
		two->next = listmerge(one, two->next, f);
		two->next->prec = two;
		two->prec = 0;
		return (two);
	}
	return (0);
}

t_dblist		*ft_mergesort(t_dblist *head, int (*f)(void *, void *))
{
	t_dblist	*splist;

	if (!head || !head->next)
		return (head);
	splist = splithalf(head);
	head = ft_mergesort(head, f);
	splist = ft_mergesort(splist, f);
	return (listmerge(head, splist, f));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblistnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:12:11 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 02:30:07 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*ft_dblistnew(void *content, size_t content_size)
{
	t_dblist	*head;

	if (!(head = (t_dblist *)ft_memalloc(sizeof(t_dblist)))
		|| !(head->data = ft_memalloc(content_size)))
		return (0);
	if (!content)
		content_size = 0;
	head->data = ft_memmove(head->data, content, content_size);
	head->d_size = content_size;
	free(content);
	return (head);
}

t_dblist	*ft_dblistpop(t_dblist *node)
{
	t_dblist	*tprec;
	t_dblist	*tnext;

	tprec = node->prec;
	tnext = node->next;
	node->next = 0;
	node->prec = 0;
	if (tprec)
		tprec->next = tnext;
	if (tnext)
		tnext->prec = tprec;
	return (tnext);
}

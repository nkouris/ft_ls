/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:35:09 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 00:54:35 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_queue_postsort(t_queue *key)
{
	t_dblist	*temp;

	temp = key->first;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		key->last = temp;
	}
}

void	ft_queue_destruc(t_queue *key, t_dblist *(*f)(t_dblist *del))
{
	t_dblist	*temp;

	temp = key->first;
	while (temp)
		temp = f(temp);
	free(key);
}

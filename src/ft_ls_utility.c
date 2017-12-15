/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:58:50 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/14 13:41:08 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	cleanup(t_lsnode *root)
{
	t_lsnode	*hold;

	while (root)
	{
		hold = root->next;
		free(root);
		root = 0;
		root = hold;
	}
}

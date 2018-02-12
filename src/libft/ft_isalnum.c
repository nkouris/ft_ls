/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:52:09 by nkouris           #+#    #+#             */
/*   Updated: 2017/09/25 16:40:51 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	int alpha;
	int digit;

	alpha = ft_isalpha(c);
	digit = ft_isdigit(c);
	if (alpha > 0 || digit > 0)
		return (1);
	else
		return (0);
}

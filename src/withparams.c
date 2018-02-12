/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   withparams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:52:19 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 01:45:48 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

void	usage_warning(char bad)
{
	ft_printf("ls: illegal option -- %c\n", bad);
	ft_printf("usage available: ls [-lartR] [file ...]\n");
	exit (0);
}

char 	*concatpath(char *fin, char *add)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(fin) + ft_strlen(add);
	if (!(temp = ft_strnew(len)))
		exit (0);
	ft_strcpy(temp, add);
	ft_strcat(temp, fin);
	return (temp);
}

int		paramatch(char *argv, t_args *args)
{
	int	found;

	found = 0;
	while (*argv)
	{
		if (*argv == 'l' ? args->l = 1 : 0)
			(argv)++ ? found++ : found;
		if (*argv == 'R' ? args->R = 1 : 0)
			(argv)++ ? found++ : found;
		if (*argv == 'a' ? args->a = 1 : 0)
			(argv)++ ? found++ : found;
		if (*argv == 'r' ? args->r = 1 : 0)
			(argv)++ ? found++ : found;
		if (*argv == 't' ? args->t = 1 : 0)
			(argv)++ ? found++ : found;
		if (!found)
			usage_warning(*argv);
	}
	return (*argv == '-' ? 0 : 1);
}

void	parseflags(char ***argv, t_args *args)
{
	if (***argv == '-')
	{
		(**argv)++;
		if (!(***argv))
		{
			(**argv)--;
			return ;
		}
		if (***argv == '-')
		{
			(**argv)++;
			if (***argv)
				usage_warning('-');
			else
			{
				(*argv)++;
				return ;
			}
		}
		if (paramatch(**argv, args) && **argv)
			(*argv)++;
	}
}

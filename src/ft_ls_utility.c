/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 12:58:50 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/17 19:31:23 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*strfpath(t_lsnode *node, char *str)
{
	char *fullpath;

	fullpath = ft_strnew(sizeof(node->name) + sizeof(str) + 1);
	ft_strcat(fullpath, (const char *)str);
	ft_strcat(fullpath, "/");
	ft_strcat(fullpath, (const char *)node->name);
	return (fullpath);
}

int			ft_numlen(int num)
{
	int i;

	i = 0;
	if (num == -2147483648)
		return (10);
	if (num < 0)
		num = num * -1;
	while (num)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

t_lssort	*create_args(void)
{
	t_lssort	*args;

	if (!(args = (t_lssort *)ft_memalloc(sizeof(t_lssort))))
		exit (1);
	return (args);
}

void		cleanup(t_lsnode *root)
{
	t_lsnode	*hold;

	while (root)
	{
		hold = root->next;
		ft_memdel((void **)&root);	
		root = hold;
	}
}

void		usage_warning(char bad)
{
	ft_printf("ls: illegal option -- %c\n", bad);
	ft_printf("usage available: ls [-lartR] [file ...]\n");
	exit (1);
}

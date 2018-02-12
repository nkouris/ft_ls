/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 10:21:05 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 04:37:47 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"
#include <stdio.h>

void	buildlevels(t_queue *explicit, t_args *args)
{
	t_dblist	*node;
	t_dblist	*hold;

	node = explicit->first;
	while (node)
	{
		if (args->mul)
			ft_printf("\n%s:\n", FPATH);
		onedir(FPATH, args);
		hold = ft_dblistpop(node);
		if (!args->rrr)
			singledelargv(node);
		else
			singledel(node);
		node = hold;
		args->mul = 1;
		if (node)
			ft_printf("\n");
	}
}

void	expfiles(t_queue *explicit, t_args *args)
{
	t_dblist	*node;

	node = explicit->first;
	while (node)
	{
		if ((SMODE & S_IFDIR) != S_IFDIR)
		{
			onefile(FPATH, args);
			args->mul = 1;
			if (node == explicit->first)
			{
				node = singledelargv(node);
				explicit->first = node;
			}
			else
			{
				singledelargv(node);
				node = node->next;
			}
		}
		else
			node = node->next;
	}
}

void	findexp(char **argv, t_args *args)
{
	t_queue		*explicit;

	parseflags(&argv, args);
	if (!(explicit = (t_queue *)ft_memalloc(sizeof(t_queue))))
		exit(0);
	if (!(*argv))
		onedir(".", args);
	while (*argv)
		multiname(*argv++, explicit);
	if (explicit->first)
		explicit->first = ft_mergesort(explicit->first, &lexosort);
	else
	{
		free(explicit);
		exit(0);
	}
	ft_queue_postsort(explicit);
	expfiles(explicit, args);
	buildlevels(explicit, args);
}

int		main(int argc, char **argv)
{
	t_args	args;

	if (argc == 1)
		onedir(".", &args);
	else
		findexp(++argv, &args);
}

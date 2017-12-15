/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:06:10 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/14 14:06:06 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		push_node(t_lsnode *new, t_lsnode **root, t_lssort *args)
{
	t_lsnode **temp;

	temp = root;
	args = 0;
	while ((*temp)->next)
		temp = &(*temp)->next;
	(*temp)->next = new;
}

void		usage_warning(char bad)
{
	ft_printf("ls: illegal option -- %c\n", bad);
	ft_printf("usage available: ls [-lartR] [file ...]\n");
	exit (1);	
}

t_lsnode	*create_node(struct dirent *element, DIR *dir)
{
	t_lsnode	*new;

	if (!(new = (t_lsnode *)ft_memalloc(sizeof(t_lsnode))))
		exit (1);
	if (element)
	{
		new->dir = dir;
		new->fserial = element->d_ino;
		new->namelen = element->d_namlen;
		new->name = (char *)ft_memalloc(new->namelen + 1);
		new->next = 0;
		ft_strcpy(new->name, (const char *)(element->d_name));
	}
	return (new);
}

t_lssort	*create_args(void)
{
	t_lssort	*args;

	if (!(args = (t_lssort *)ft_memalloc(sizeof(t_lssort))))
		exit (1);
	return (args);
}

void		parse_args(char ***argv, t_lssort *args)
{
	int found;

	if ((*argv)[1][0] == '-')
	{
		(*argv)++;
		(**argv)++;
		while (***argv)
		{
			found = 0;
			if (***argv == 'l' ? (args)->l = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 'R' ? (args)->R = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 'a' ? (args)->a = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 'r' ? (args)->r = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 't' ? (args)->t = 1 : 0)
				(**argv)++ ? found++ : found;
			if (!found)
				usage_warning(***argv);
		}
	}
	else
		free(args);
}

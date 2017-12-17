/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:06:10 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/16 15:02:33 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		push_node(t_lsnode *node, t_lsnode **root, t_lssort *args)
{
	t_lsnode **temp;

	temp = root;
	args = 0;
	while ((*temp)->next)
	{
		if ((*temp)->m_bytelen < node->m_bytelen)
			(*temp)->m_bytelen = node->m_bytelen;
		else
			node->m_bytelen = (*temp)->m_bytelen;
		if ((*temp)->m_nlink < node->m_nlink)
			(*temp)->m_nlink = node->m_nlink;
		else
			node->m_nlink = (*temp)->m_nlink;
		temp = &(*temp)->next;
	}
	(*temp)->next = node;
}

void		usage_warning(char bad)
{
	ft_printf("ls: illegal option -- %c\n", bad);
	ft_printf("usage available: ls [-lartR] [file ...]\n");
	exit (1);	
}

t_lsnode	*create_node(struct dirent *element, DIR *dir)
{
	t_lsnode	*node;
	struct stat	*sbuf;

	if (!(node = (t_lsnode *)ft_memalloc(sizeof(t_lsnode)))
		|| !(sbuf = (struct stat *)ft_memalloc(sizeof(struct stat))))
		exit (1);
/* Gather base info */
	if (element)
	{
		node->dir = dir;
		node->namelen = element->d_namlen;
		node->name = (char *)ft_memalloc(node->namelen + 1);
		node->next = 0;
		node->sbuf = sbuf;
		ft_memset(node->perms, '-', 10);
		ft_strcpy(node->name, (const char *)(element->d_name));
/* Gather stat info */
		stat((const char *)node->name, sbuf);
		node->m_bytelen = ft_numlen(node->sbuf->st_size);
		node->m_nlink = ft_numlen(node->sbuf->st_nlink);
		cat_files(node);
	}
	else
		ft_memdel((void **)&sbuf);
	return (node);
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
		ft_memdel((void **)&args);
}

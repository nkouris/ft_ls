/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:06:10 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/17 21:09:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define SNODE node->sbuf->st_mode
/*
void		pmarks(t_lsnode *node)
{
	if (node->perms[0] == 'l')
	{
		stat
}
*/
void		cat_files(t_lsnode *node)
{
	if ((SNODE & S_IFDIR) == S_IFDIR)
		node->perms[0] = 'd';
	if ((SNODE & S_IFLNK) == S_IFLNK)
		node->perms[0] = 'l';
	if ((SNODE & S_IRUSR) == S_IRUSR)
		node->perms[1] = 'r';
	if ((SNODE & S_IWUSR) == S_IWUSR)
		node->perms[2] = 'w';
	if ((SNODE & S_IXUSR) == S_IXUSR)
		node->perms[3] = 'x';
	if ((SNODE & S_IRGRP) == S_IRGRP)
		node->perms[4] = 'r';
	if ((SNODE & S_IWGRP) == S_IWGRP)
		node->perms[5] = 'w';
	if ((SNODE & S_IXGRP) == S_IXGRP)
		node->perms[6] = 'x';
	if ((SNODE & S_IROTH) == S_IROTH)
		node->perms[7] = 'r';
	if ((SNODE & S_IWOTH) == S_IWOTH)
		node->perms[8] = 'w';
	if ((SNODE & S_IXOTH) == S_IXOTH)
		node->perms[9] = 'x';
//	pmarks(node);
}

void		push_node(t_lsnode *node, t_lsnode **root, t_lssort *args)
{
	t_lsnode **temp;

	temp = root;
	args = 0;
	if (!(*temp)->next)
		fwidth_match(temp, node);
	while ((*temp)->next)
	{
		fwidth_match(temp, node);	
		temp = &(*temp)->next;
	}
	(*temp)->next = node;
}

t_lsnode	*create_node(struct dirent *element, DIR *dir, char *str)
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
		node->name = (char *)ft_memalloc(sizeof(element->d_name) + 1);
		node->sbuf = sbuf;
		ft_memset(node->perms, '-', 10);
		ft_strcpy(node->name, (const char *)(element->d_name));
/* Gather stat info */
		node->fullpath = strfpath(node, str);
		lstat((const char *)node->fullpath, sbuf);
/* Gather username and group */
		use_stats(node);
		cat_files(node);
	}
	else
		ft_memdel((void **)&sbuf);
	return (node);
}

void		check_args(char ***argv, t_lssort **args)
{
	int found;

	if ((*++(*argv))[0] == '-')
	{
		(**argv)++;
		while (***argv)
		{
			found = 0;
			if (***argv == 'l' ? (*args)->l = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 'R' ? (*args)->R = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 'a' ? (*args)->a = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 'r' ? (*args)->r = 1 : 0)
				(**argv)++ ? found++ : found;
			if (***argv == 't' ? (*args)->t = 1 : 0)
				(**argv)++ ? found++ : found;
			if (!found)
				usage_warning(***argv);
		}
		(*argv)++;
	}
	else
		ft_memdel((void **)args);
}

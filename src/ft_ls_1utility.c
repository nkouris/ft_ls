/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_1utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 20:48:26 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/19 20:02:26 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Function to fill node with info gathered from data points contained in
// struct stat

void		use_stats(t_lsnode *node)
{
	node->pass = getpwuid(NSBUF->st_uid);
	node->group = getgrgid(NSBUF->st_gid);
	node->m_bytelen = ft_numlen(NSBUF->st_size);
	node->m_nlink = ft_numlen(NSBUF->st_nlink);
	ft_strcpy(node->time,
	(const char *)ctime((const time_t *)&(NSBUF->st_mtimespec.tv_sec)));
	if (node->perms[0] == 'b' || node->perms[0] == 'c')
	{
		node->special = 1;
		node->majordev = major(NSBUF->st_dev);
		node->minordev = minor(NSBUF->st_dev);
		node->m_devlen = ft_numlen(node->majordev) + ft_numlen(node->minordev);
	}
}

// Function to compare and pass values as nodes are added to the list

void		fwidth_match(t_lsnode **temp, t_lsnode *node)
{
	if ((*temp)->m_bytelen < node->m_bytelen)
		(*temp)->m_bytelen = node->m_bytelen;
	else
		node->m_bytelen = (*temp)->m_bytelen;
	if ((*temp)->m_devlen < node->m_devlen)
		(*temp)->m_devlen = node->m_devlen;
	else
		node->m_devlen = (*temp)->m_devlen;
	if ((*temp)->m_nlink < node->m_nlink)
		(*temp)->m_nlink = node->m_nlink;
	else
		node->m_nlink = (*temp)->m_nlink;
	if ((*temp)->multi)
		node->multi = 1;
	if ((*temp)->special)
		node->special = 1;
	temp = &(*temp)->next;
}

// Self-explanatory, will fill the list node with relevant info

void	fill_node(t_lsnode *node, t_lsnode *root, char *str, 
		struct dirent *element)
{
	struct stat *sbuf;

	if (!(node->name = (char *)ft_memalloc(sizeof(element->d_name) + 1))
		|| !(sbuf = (struct stat *)ft_memalloc(sizeof(struct stat))))
		exit (1);
	node->dir = root->dir;
	node->sbuf = sbuf;
	ft_memset(node->perms, '-', 10);
	ft_strcpy(node->name, (const char *)(element->d_name));
	node->fullpath = strfpath(node, str);
	node->multi = root->multi;
	lstat((const char *)node->fullpath, sbuf);
	cat_files(node);
	use_stats(node);
}

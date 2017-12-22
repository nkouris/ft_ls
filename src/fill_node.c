/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 20:48:26 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/21 18:59:27 by nkouris          ###   ########.fr       */
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

void		fieldwidth_match(t_lsnode *top, t_lsnode *node)
{
	if (top->m_bytelen < node->m_bytelen)
		top->m_bytelen = node->m_bytelen;
	else
		node->m_bytelen = top->m_bytelen;
	if (top->m_devlen < node->m_devlen)
		top->m_devlen = node->m_devlen;
	else
		node->m_devlen = top->m_devlen;
	if (top->m_nlink < node->m_nlink)
		top->m_nlink = node->m_nlink;
	else
		node->m_nlink = top->m_nlink;
	if (top->multi)
		node->multi = 1;
	if (top->special)
		node->special = 1;
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
	node->namelen = element->d_namlen;
	node->fullpath = strfpath(node, str);
	node->multi = root->multi;
	lstat((const char *)node->fullpath, sbuf);
	cat_files(node);
	use_stats(node);
}

#define SNODE node->sbuf->st_mode

void		type_file(t_lsnode *node)
{
	if ((SNODE & S_IFDIR) == S_IFDIR)
		node->perms[0] = 'd';
	if ((SNODE & S_IFCHR) == S_IFCHR)
		node->perms[0] = 'c';
	if ((SNODE & S_IFBLK) == S_IFBLK)
		node->perms[0] = 'b';
	if ((SNODE & S_IFLNK) == S_IFLNK)
		node->perms[0] = 'l';
	if ((SNODE & S_IFSOCK) == S_IFSOCK)
		node->perms[0] = 's';
	if ((SNODE & S_IFIFO) == S_IFIFO)
		node->perms[0] = 'p';
}

void		cat_files(t_lsnode *node)
{
	type_file(node);
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
}

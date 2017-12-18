/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_1utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 20:48:26 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/17 21:07:10 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		use_stats(t_lsnode *node)
{
	node->pass = getpwuid(NSBUF->st_uid);
	node->group = getgrgid(NSBUF->st_gid);
	node->m_bytelen = ft_numlen(NSBUF->st_size);
	node->m_nlink = ft_numlen(NSBUF->st_nlink);
	ft_strcpy(node->time,
	(const char *)ctime((const time_t *)&(NSBUF->st_mtimespec.tv_sec)));
}

void		fwidth_match(t_lsnode **temp, t_lsnode *node)
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

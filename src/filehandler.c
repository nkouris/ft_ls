/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filehandler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:30:34 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 03:44:11 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

int		setlstat(char *str, t_info *info)
{
	struct stat buf;

	if (lstat(str, &buf))
	{
		if (info->name)
			ft_printf("ftls: %s: %s\n", info->name, strerror(errno));
		else
			ft_printf("ftls: %s: %s\n", str, strerror(errno));
		return (0);
	}
	else
	{
		info->sbuf = (struct stat *)ft_memalloc(sizeof(struct stat));
		ft_memcpy(info->sbuf, &buf, sizeof(struct stat));
	}
	return (1);
}

t_dblist	*singledelargv(t_dblist *del)
{
	t_dblist	*next;

	next = del->next;
	ft_dblistpop(del);
	if (((t_info *)(del->data))->sbuf)
		free(((t_info *)(del->data))->sbuf);
	if (((t_info *)(del->data))->fullpath)
		free(((t_info *)(del->data))->fullpath);
	free(del->data);
	free(del);
	return (next);
}


t_dblist	*singledel(t_dblist *del)
{
	t_dblist	*next;

	next = del->next;
	ft_dblistpop(del);
	if (((t_info *)(del->data))->sbuf)
		free(((t_info *)(del->data))->sbuf);
	if (((t_info *)(del->data))->fullpath)
		free(((t_info *)(del->data))->fullpath);
	if (((t_info *)(del->data))->name)
		free(((t_info *)(del->data))->name);
	free(del->data);
	free(del);
	return (next);
}

void	pophidden(t_queue *level)
{
	t_dblist	*del;

	while (*(((t_info *)(level->first->data))->name) == '.')
	{
		del = ft_popfront(level);
		singledel(del);
		if (!level->first)
			break ;
	}
}

int		lexosort(void *one, void *two)
{
	int			comp;
	t_info		*a;
	t_info		*b;

	a = (t_info *)one;
	b = (t_info *)two;
	if (!a->entry || !b->entry)
		comp = ft_strcmp(a->fullpath, b->fullpath);
	else
		comp = ft_strcmp(a->name, b->name); 
	if (comp < 1)
		return (1);
	return (2);
}

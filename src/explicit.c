/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explicit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:52:50 by nkouris           #+#    #+#             */
/*   Updated: 2018/01/05 14:22:16 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		stat_check(t_lsnode *new, struct stat *sbuf, char *str)
{
	if ((lstat((const char *)new->name, sbuf)) < 0)
	{
		new->fullpath = strfpath(new, ".");
		if ((lstat((const char *)new->fullpath, sbuf)) < 0)
			return (0);
	}
	else
		new->fullpath = str;
	return (1);
}

int		solo_check(t_lsnode **top, char *str, t_lssort *args)
{
	t_lsnode	*new;
	struct stat	*sbuf;

	if (!(*top)->name)
		new = (*top);
	else 
		new = (t_lsnode *)ft_memalloc(sizeof(t_lsnode));
	if (!(sbuf = (struct stat *)ft_memalloc(sizeof(struct stat))) || !new)
		exit (1);
	new->name = str;
	new->sbuf = sbuf;
	if (!stat_check(new, sbuf, str))
		return (0);
	ft_memset(new->perms, '-', 10);
	use_stats(new);
	cat_files(new);
	if (new->perms[0] != 'd')
		new->solo = 1;
	args->exp = 1;
	if ((*top) == new)
		fieldwidth_match(args, (*top));
	else
		push_level(new, top, args);
	return (1);
}

int		explicit(t_lsnode **top, t_lssort *args, char *str)
{
	if (!solo_check(top, str, args))
	{
		ft_printf("ls: %s: No such file or directory\n", str);
		return (0);
	}
	else
		return (1);
}

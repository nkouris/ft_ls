/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explicit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:52:50 by nkouris           #+#    #+#             */
/*   Updated: 2017/12/21 19:07:25 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		solo_check(t_lsnode **top, char *str, t_lssort *args)
{
	t_lsnode	*new;
	struct stat	*sbuf;

	if (!(new = ft_memalloc(sizeof(t_lsnode)))
		|| !(sbuf = (struct stat *)ft_memalloc(sizeof(struct stat))))
		return (0);
	new->name = str;
	new->sbuf = sbuf;
	if ((lstat((const char *)new->name, sbuf)) < 0)
	{
		new->fullpath = strfpath(new, ".");
		if ((lstat((const char *)new->fullpath, sbuf)) < 0)
			return (0);
	}
	ft_memset(new->perms, '-', 10);
	new->solo = 1;
	new->multi = (*top)->multi;
	use_stats(new);
	cat_files(new);
	if (!(*top)->name)
		(*top) = new;
	else
		push_level(*top, &new, args);
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

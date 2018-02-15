/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 11:28:26 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/14 17:18:16 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

void	getperms(char **perm, t_dblist *node, t_args *args)
{
	((SMODE & S_IFDIR) == S_IFDIR) ? (*perm)[0] = 'd' : (*perm)[0];
	((SMODE & S_IFCHR) == S_IFCHR) ? (*perm)[0] = 'c' : (*perm)[0];
	((SMODE & S_IFBLK) == S_IFBLK) ? (*perm)[0] = 'b' : (*perm)[0];
	((SMODE & S_IFLNK) == S_IFLNK) ? (*perm)[0] = 'l' : (*perm)[0];
	((SMODE & S_IFSOCK) == S_IFSOCK) ? (*perm)[0] = 's' : (*perm)[0];
	((SMODE & S_IFIFO) == S_IFIFO) ? (*perm)[0] = 'p' : (*perm)[0];
	((SMODE & S_IRUSR) == S_IRUSR) ? (*perm)[1] = 'r' : (*perm)[1];
	((SMODE & S_IWUSR) == S_IWUSR) ? (*perm)[2] = 'w' : (*perm)[2];
	((SMODE & S_IXUSR) == S_IXUSR) ? (*perm)[3] = 'x' : (*perm)[3];
	((SMODE & S_IRGRP) == S_IRGRP) ? (*perm)[4] = 'r' : (*perm)[4];
	((SMODE & S_IWGRP) == S_IWGRP) ? (*perm)[5] = 'w' : (*perm)[5];
	((SMODE & S_IXGRP) == S_IXGRP) ? (*perm)[6] = 'x' : (*perm)[6];
	((SMODE & S_IROTH) == S_IROTH) ? (*perm)[7] = 'r' : (*perm)[7];
	((SMODE & S_IWOTH) == S_IWOTH) ? (*perm)[8] = 'w' : (*perm)[8];
	((SMODE & S_IXOTH) == S_IXOTH) ? (*perm)[9] = 'x' : (*perm)[9];
	if ((*perm)[0] == 'c')
		args->links = 1;
}

void	widthcalc(t_dblist *node, t_width *width)
{
	int		linklen;
	int		usnlen;
	int		grplen;
	int		bytelen;
	int		majlen;
	int		minlen;

	linklen = ft_numlen(LINKS);
	usnlen = ft_strlen(USER);
	grplen = ft_strlen(GROUP);
	bytelen = ft_numlen(BYTES);
	majlen = ft_numlen((int)MAJOR);
	minlen = ft_numlen((int)MINOR);
	(width->col1 < linklen) ? width->col1 = linklen : width->col1;
	(width->col2 < usnlen) ? width->col2 = usnlen : width->col2;
	(width->col3 < grplen) ? width->col3 = grplen : width->col3;
	(width->col4 < bytelen) ? width->col4 = bytelen : width->col4;
	(width->devmaj < majlen) ? width->devmaj = majlen : width->devmaj;
	(width->devmin < minlen) ? width->devmin = minlen : width->devmin;
}

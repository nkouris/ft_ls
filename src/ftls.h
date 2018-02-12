/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 10:46:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/12 03:30:20 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLS_H
# define FTLS_H

# include "libft.h"
# include "ftprintf.h"
# include <dirent.h>
# include <stdbool.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>

typedef struct			s_info
{
		struct dirent	*entry;
		struct stat		*sbuf;
		char			*fullpath;
		char			*name;
}						t_info;

typedef struct			s_args
{
		bool			R;
		bool			r;
		bool			l;
		bool			t;
		bool			a;
		bool			mul;
		bool			rec;
}						t_args;


/*
**		printing ...............................................................
*/

void		printlevel(t_queue *level, t_args *args);

/*
**		filehandler ............................................................
*/

int			setlstat(char *str, t_info *info);
void		pophidden(t_queue *level);
t_dblist	*singledel(t_dblist *node);
int			lexosort(void *one, void *two);
t_dblist	*singledelargv(t_dblist *node);

/*
**		withparams .............................................................
*/

void		parseflags(char ***argv, t_args *args);
char		*concatpath(char *fin, char *add);

#endif

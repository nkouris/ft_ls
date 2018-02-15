/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 10:46:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/02/14 17:18:14 by nkouris          ###   ########.fr       */
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
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

# define SMODE (((t_info *)(node->data))->sbuf->st_mode)
# define SFUB (((t_info *)(node->data))->sbuf)
# define FPATH (((t_info *)(node->data))->fullpath)
# define NAME (((t_info *)(node->data))->name)
# define IFPATH (info->fullpath)
# define INAME (info->name)
# define NAME (((t_info *)(node->data))->name)
# define BLOCK (((t_info *)(node->data))->sbuf->st_blocks)
# define LINKS (((t_info *)(node->data))->sbuf->st_nlink) 
# define USER ((getpwuid(((t_info *)(node->data))->sbuf->st_uid))->pw_name)
# define GROUP ((getgrgid(((t_info *)(node->data))->sbuf->st_gid))->gr_name)
# define BYTES (((t_info *)(node->data))->sbuf->st_size)
# define MAJOR (major(((t_info *)(node->data))->sbuf->st_rdev))
# define MINOR (minor(((t_info *)(node->data))->sbuf->st_rdev))
# define TIME (ctime(&(SFUB->st_mtimespec.tv_sec)))

typedef struct			s_info
{
	struct dirent		*entry;
	struct stat			*sbuf;
	char				*fullpath;
	char				*name;
}						t_info;

typedef struct			s_args
{
	bool				rrr;
	bool				r;
	bool				l;
	bool				t;
	bool				a;
	bool				mul;
	bool				rec;
	bool				links;
}						t_args;

typedef struct			s_width
{
	int					col1;
	int					col2;
	int					col3;
	int					col4;
	int					devmaj;
	int					devmin;
}						t_width;


/*
**		collectl ...............................................................
*/

void					getperms(char **perm, t_dblist *node, t_args *args);
void					widthcalc(t_dblist *node, t_width *width);

/*
**		dive ...................................................................
*/

t_dblist				*newlevel(t_dblist *node, t_args *args);
void					subdirdive(t_queue *level, t_args *args);

/*
**		accruedata .............................................................
*/

void					multiname(char *str, t_queue *explicit);
void					onefile(char *name, t_args *args);
t_queue					*buildir(DIR *d_base, char *base);
void					onedir(char *base, t_args *args);

/*
**		printing ...............................................................
*/

void					printlevel(t_queue *level, t_args *args);

/*
**		filehandler ............................................................
*/

int						setlstat(char *str, t_info *info);
void					pophidden(t_queue *level);
t_dblist				*singledel(t_dblist *node);
int						lexosort(void *one, void *two);
t_dblist				*singledelargv(t_dblist *node);

/*
**		withparams .............................................................
*/

void					parseflags(char ***argv, t_args *args);
char					*concatpath(char *fin, char *add);

#endif

#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <errno.h>


/* DELETE */
#include <string.h>

#define NSBUF node->sbuf

typedef	struct		s_lsnode
{
	DIR				*dir;
	ino_t			fserial;
	char			time[26];
	char			*fullpath;
	char			*dirstr;
	char			*name;
	char			perms[12];
	char			*link;
	int				namelen;
	int				majordev;
	int				minordev;
	unsigned int	m_nlink;
	unsigned int	m_bytelen;
	unsigned int	m_usnlen;
	unsigned int	m_datelen;
	unsigned int	m_devlen;
	struct stat		*sbuf;
	struct passwd	*pass;
	struct group	*group;
/* Switches */
	unsigned int	isdir : 1;
	unsigned int	skip : 1;
	unsigned int	solo : 1;
	unsigned int	multi : 1;
	unsigned int	special : 1;
/* Link */
// covers directory level listing
	struct s_lsnode	*next;
// pointer to descend into subdirectory level listing
	struct s_lsnode *subdir;
}					t_lsnode;

typedef struct		s_args
{
	unsigned int	R : 1;
	unsigned int	r : 1;
	unsigned int	a : 1;
	unsigned int	l : 1;
	unsigned int	t : 1;
	unsigned int	exp : 1;
	unsigned int	m_nlink;
	unsigned int	m_bytelen;
	unsigned int	m_usnlen;
	unsigned int	m_datelen;
	unsigned int	m_devlen;

}					t_lssort;

/**
 * Start.c 
**/

void		subdir_dive(t_lsnode *top, t_lssort *args);
void		print_directories(t_lsnode *top, t_lssort *args);
void		current_dir(t_lsnode **top, t_lssort *args, char *fname);

/**
 * Node_Creation.c
**/

void		cat_files(t_lsnode *node);
void		push_level(t_lsnode *new, t_lsnode **top, t_lssort *args);
t_lsnode	*create_node(struct dirent *element, t_lsnode *top, char *str);

/**
 * Explicit.c
**/

void		argsact(t_lssort *args, t_lsnode **top);
int			explicit(t_lsnode **top, t_lssort *args, char *str);

/**
 * Utility.c
**/

char		*strfpath(t_lsnode *top, char *str);
int			ft_numlen(int num);
void		cleanup(t_lsnode *top);
void		usage_warning(char bad);

/*
 * FillNode.c
**/

void		use_stats(t_lsnode *node);
void		fieldwidth_match(t_lssort *args, t_lsnode *node);
void		fill_node(t_lsnode *node, t_lsnode *top, char *str,
			struct dirent *element);
void		type_file(t_lsnode *node);
void		cat_files(t_lsnode *node);

/*
 * ListHandling.c
**/

void		rmhidden(t_lsnode **top);
int			check_args(char ***argv, t_lssort **args);
void		clean_level(t_lsnode **top, t_lsnode **temp, t_lssort *args);

#endif

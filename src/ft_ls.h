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
	struct s_lsnode	*next;
}					t_lsnode;

typedef struct		s_args
{
	unsigned int	R : 1;
	unsigned int	r : 1;
	unsigned int	a : 1;
	unsigned int	l : 1;
	unsigned int	t : 1;
}					t_lssort;

/**
 * FT_LS_BASE
**/

void		print_directories(t_lsnode *root, t_lssort *args);

/**
 * FT_LS_HANDLING
**/

void		cat_files(t_lsnode *node);
void		push_node(t_lsnode *new, t_lsnode **root, t_lssort *args);
t_lsnode	*create_node(struct dirent *element, DIR *dir, char *str,
			unsigned int multi);
void		check_args(char ***argv, t_lssort **args);


/**
 * FT_LS_LISTHANDLING
**/

void		argsact(t_lssort *args, t_lsnode **root);

/**
 * FT_LS_EXPLICIT
**/

int			solo_check(t_lsnode **root, char *str, t_lssort *args);

/**
 * FT_LS_UTILITY
**/

void		cleanup(t_lsnode *root);
int			ft_numlen(int num);
t_lssort	*create_args(void);
void		usage_warning(char bad);
char		*strfpath(t_lsnode *root, char *str);

/*
 * FT_LS_1UTILITY
**/

void		use_stats(t_lsnode *node);
void		fwidth_match(t_lsnode **root, t_lsnode *node);
void		id_dirstr(t_lsnode *node);

#endif

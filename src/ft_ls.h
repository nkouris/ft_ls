#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef	struct		s_lsnode
{
	DIR				*dir;
	ino_t			fserial;
	char			*name;
	unsigned int	namelen;
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
 * FT_LS_HANDLING
**/

void		push_node(t_lsnode *new, t_lsnode **root, t_lssort *args);
t_lsnode	*create_node(struct dirent *element, DIR *dir);
t_lssort	*create_args(void);
void		parse_args(char ***argv, t_lssort *args);

/**
 * FT_LS_UTILITY
**/

void		cleanup(t_lsnode *root);

#endif

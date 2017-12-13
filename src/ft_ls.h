#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef	struct		s_lsleaf
{
	DIR				*dir;
	ino_t			fserial;
	char			*name;
	unsigned int	namelen;
	struct s_lsleaf	*left;
	struct s_lsleaf	*right;
}					t_lsleaf;

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

t_lsleaf	*create_leaf(struct dirent *element);
t_lssort	*create_args(void);
void		parse_args(char ***argv, t_lssort **args);

#endif

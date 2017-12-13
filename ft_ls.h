#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

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
}

/**
 * FT_LS_HANDLING
**/

void	parse_args(char ***argv, t_lssort **args);

#endif

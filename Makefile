PROGRAM = ftls
NAME = libftls.a 
FLAGS = -Wall -Werror -Wextra -g
CC = gcc
OBJSRC = $(patsubst %, %.o, $(SRC))
OBJINC = $(patsubst %, %.o, $(INC))

# LS SOURCE
SRC += src/ft_ls_base
SRC += src/ft_ls_handling
SRC += src/ft_ls_listhandling
SRC += src/ft_ls_utility
SRC += src/ft_ls_1utility
SRC += src/ft_ls_explicit

# GENERAL LIBFT FUNCTIONS
INC += src/libft/ft_memalloc
INC += src/libft/ft_strlen
INC += src/libft/ft_memalloc
INC += src/libft/ft_strcpy
INC += src/libft/ft_bzero
INC += src/libft/ft_isalpha
INC += src/libft/ft_isdigit
INC += src/libft/ft_memdel
INC += src/libft/ft_memset
INC += src/libft/ft_strncpy
INC += src/libft/ft_strcat
INC += src/libft/ft_strnew

# FTPRINTF
INC += src/libft/ftprintf/conversion_diou
INC += src/libft/ftprintf/dispatcher
INC += src/libft/ftprintf/printflags
INC += src/libft/ftprintf/conversion_sc
INC += src/libft/ftprintf/storeflags
INC += src/libft/ftprintf/conversion_xp
INC += src/libft/ftprintf/misc
INC += src/libft/ftprintf/ulitobase

all: $(NAME)

$(NAME): $(OBJINC) $(OBJSRC)
	@ echo "Building static library..."
	@ ar -rcs $(NAME) $(OBJSRC) $(OBJINC)
	@ echo "Compiling ftls program"
	@ $(CC) $(FLAGS) -L . -l ftls -o $(PROGRAM)

%.o: %.c
	@ echo "Compiling $<..."
	@ $(CC) $(FLAGS) -c $< -o $@

clean:
	@ /bin/rm -f $(OBJSRC)
	@ /bin/rm -f $(OBJINC)
	@ echo "Cleaning folders of object files..."

fclean: clean
	@ /bin/rm -f $(NAME)
	@ /bin/rm -f $(PROGRAM)
	@ echo "Removing library file and binary..."

re: fclean all
	@ echo "Program Remade"

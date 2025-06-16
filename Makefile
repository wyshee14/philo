# color
GREEN = \033[0;32m
WHITE = \033[0m

#Program Name
NAME = philo

#The -I (uppercase i) flag is used to add a directory to the list of directories
#the compiler searches for header files (#include directives).
#Directories
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_DIR = include/
SRC_DIR = src/
INC = -I$(INC_DIR)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O3 -I$(INC_DIR) -I$(LIBFT_DIR)

#Source Files
#addprefix <prefix>, <list>
#<prefix> is the string that added to the beginning of each word
SRC = \
$(wildcard $(SRC_DIR)*.c) \
#SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
#BUILTIN = $(addprefix $(BUILTIN_DIR), $(BUILTIN_FILES))

OBJ_SRC = $(SRC:.c=.o)

all: $(NAME)

# -L tells the linker where to look for libraries -L<directory>
$(NAME) : $(OBJ_SRC)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_SRC) $(LIBFT) -o $(NAME) -pthread
	@echo "$(GREEN)-----COMPILED DONE-----\n"

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_SRC)
	@make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)-----FULLY REMOVED-----\n$(WHITE)"

re: fclean all

norm:
	@echo "----- check include -----"
	@norminette include/
	@echo "\n----- check libft -----"
	@norminette libft/
	@echo "\n----- check src -----"
	@norminette src/

.PHONY: all clean fclean re norm

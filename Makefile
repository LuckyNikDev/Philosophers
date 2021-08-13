NAME = philo

LIST =  main.c utils.c utils2.c init.c init2.c 

# LIST_B = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c src_bonus/main_bonus.c src_bonus/utils_bonus.c src_bonus/utils_two_bonus.c

OBJ = $(patsubst %.c, %.o, $(LIST))

# OBJ_B = $(patsubst %.c, %.o, $(LIST_B))

HEAD = philosophers.h

# BONUS_BIN = ./pipex_bonus

# HEAD_B = src_bonus/pipex_bonus.h

# DIR = ./libft_finish

# LIB = libft_finish/libft.a

FLAGS = -Wall -Wextra -Werror -pthread

all	: $(NAME)

$(NAME)	: $(OBJ) $(HEAD)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

%.o	: %.c
	gcc $(FLAGS) -c $< -o $@

clean	:
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

# bonus	: $(BONUS_BIN)

# $(BONUS_BIN): $(OBJ_B) $(HEAD_B)
	# $(MAKE) -C $(DIR)
	# gcc $(FLAGS) $(LIB) $(OBJ_B) -o $(BONUS_BIN)

re	 : fclean all

.PHONY	: all clean fclean re
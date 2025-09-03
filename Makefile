NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft
LDFLAGS = -lreadline -lhistory

RM = rm -rf

SRCS = 

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
LIBFT_DIR = libft

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT)
	make -C $(LIBFT_DIR)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(OBJS)
	make clean -C libft

re : fclean all

.PHONY: all clean fclean re

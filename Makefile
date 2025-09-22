NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft
LDFLAGS = -lreadline -lhistory

RM = rm -rf

SRCS = srcs/main.c \
       srcs/bltins/pwd.c \
       srcs/bltins/env.c \
       srcs/bltins/echo.c \
       srcs/bltins/cd.c \
       srcs/bltins/cd_utils.c \
       srcs/bltins/exit.c \
       srcs/bltins/exit_utils.c \
       srcs/bltins/export.c \
       srcs/bltins/unset.c \
       srcs/bltins/run_bltins.c \
       srcs/utils/env_utils.c \
       srcs/utils/signal.c \
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

NAME = minishell

CC = cc

INCLUDES = -Iincludes -Ilibft

CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -lreadline -lhistory

RM = rm -rf

SRCS = srcs/main.c \
       srcs/bltins/pwd.c \
       srcs/bltins/env.c \
       srcs/bltins/echo.c \
       srcs/bltins/cd_utils.c \
       srcs/bltins/exit.c \
       srcs/bltins/exit_utils.c \
       srcs/parser/ft_strtok.c \
       srcs/parser/parse.c \
       srcs/parser/parse_cleanup.c \
       srcs/parser/parse_utils.c \
       srcs/parser/parse_utils1.c \
       srcs/parser/parse_builtin.c \
       srcs/unpacker/dollar.c \
       srcs/unpacker/unquoted.c \
       srcs/unpacker/handle_single_quotes.c \
       srcs/unpacker/handle_double_quotes.c \
       srcs/unpacker/unpack_token.c \
       srcs/error/redir_error.c \
       srcs/redirections/file_handle.c \
       srcs/redirections/redirect.c \
       srcs/redirections/free_utils.c \
       srcs/redirections/redirect_out.c \
       srcs/redirections/redirect_append_out.c \
       srcs/redirections/redirect_in.c \
       srcs/redirections/redirect_heredoc.c \
       srcs/redirections/redirect_utils.c \
       srcs/redirections/redirect_utils1.c \
       srcs/redirections/redirect_rephrase.c \
       srcs/redirections/redirect_rephrase1.c \
       srcs/exec/exec_cmd.c \
       srcs/exec/exec_cmd_utils.c \
       srcs/exec/read_heredoc.c

OBJS = $(SRCS:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

LIBFT = -Llibft -lft
LIBFT_DIR = libft

all : $(NAME) clean

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(OBJS)
	make clean -C libft

re : fclean all

.PHONY: all clean fclean re

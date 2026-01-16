NAME = minishell

CC = cc

INCLUDES = -Iincludes -Ilibft

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lreadline -lhistory

RM = rm -rf

SRCS = srcs/main.c \
	srcs/bltins/cd.c \
	srcs/bltins/pwd.c \
	srcs/bltins/unset.c \
	srcs/bltins/export.c \
	srcs/bltins/env.c \
	srcs/bltins/echo.c \
	srcs/bltins/cd_utils.c \
	srcs/bltins/exit.c \
	srcs/bltins/exit_utils.c \
	srcs/bltins/run_bltins.c \
	srcs/utils/env_utils.c \
	srcs/utils/signal.c \
	srcs/utils/heredoc_signal.c \
	srcs/utils/shlvl.c \
	srcs/parser/parse.c \
	srcs/parser/check_line.c \
	srcs/parser/parse_line.c \
	srcs/parser/parse_lineutil.c \
	srcs/parser/parse_cleanup.c \
	srcs/parser/parse_utils.c \
	srcs/parser/parse_utils1.c \
	srcs/parser/parse_builtin.c \
	srcs/unpacker/dollar.c \
	srcs/unpacker/append.c \
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
	srcs/exec/exec_cmd_prep_file.c \
	srcs/exec/exec_cmd_utils.c \
	srcs/exec/exec_cmd_utils1.c \
	srcs/exec/read_heredoc.c \
	srcs/exec/read_heredoc_util.c

OBJS = $(SRCS:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

LIBFT = libft/libft.a

LIBFT_DIR = libft

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

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

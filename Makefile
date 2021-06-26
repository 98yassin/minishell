NAME = minishell

CFLAGS = -Wall -Wextra -Werror

src = shell.c lexer.c expanding.c parce.c env.c

libft = ./libft/libft.a

OBJ = $(src:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@gcc $(CFLAGS) $(OBJ) $(libft) -o $(NAME) -lreadline

clean:
	rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all
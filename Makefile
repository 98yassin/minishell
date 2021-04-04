NAME = minishell

CFLAGS = -Wall -Wextra -Werror

src = shell.c get_next_line.c lexer.c expanding.c

libft = ./libft/libft.a

OBJ = $(src:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@gcc $(CFLAGS) $(OBJ) $(libft) -o $(NAME)

clean:
	rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all
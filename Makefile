NAME = minishell

CFLAGS = -Wall -Wextra -Werror

src = shell.c lexer.c expanding.c parce.c env.c

libft = ./libft/libft.a

HDRS = ./minishell.h

OBJ = $(src:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	make -sC libft
	gcc $(CFLAGS) $^ $(libft) -o $(NAME) -lreadline

%.o: %.c $(HDRS)
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make -sC libft clean

fclean: clean
	rm -f $(NAME)
	@make -sC libft fclean

re: fclean all
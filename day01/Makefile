.PHONY: all fclean

NAME1 = part_1_get_pass

NAME2 = part_2_get_real_pass

LIBFT = ../libft/libft.a

FLAGS = -Wall -Werror -Wextra -g3 -I ../libft/ -L ../libft/ -lft

all: $(NAME1) $(NAME2)

part_1: $(NAME1)
	@./$(NAME1)

$(NAME1): $(NAME1).c $(LIBFT)
	@cc $(NAME1).c $(FLAGS) -o $(NAME1)

part_2: $(NAME2)
	@./$(NAME2)

$(NAME2): $(NAME2).c $(LIBFT)
	@cc $(NAME2).c $(FLAGS) -o $(NAME2)

$(LIBFT):
	@make -C ../libft/

clean:
	rm -f $(NAME1) $(NAME2)

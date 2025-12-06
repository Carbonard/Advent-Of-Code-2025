.PHONY: all fclean

NAME1 = part_1_sum_grand_total

NAME2 = part_2_cephalopod_math

LIBFT = ../libft/libft.a

FLAGS = -Wall -Werror -Wextra -g3 -I ../libft/ -L ../libft/ -lft -lgmp

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

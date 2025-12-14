.PHONY: all fclean

NAME1 = part_1_fit_gifts

LIBFT = ../libft/libft.a

LIBARRAYS = ../dynamic_arrays/libft_dynarray.a

FLAGS = -Wall -Werror -Wextra -O3 -I ../libft/ -L ../libft/ -lft -I ../dynamic_arrays/src -L ../dynamic_arrays/ -lft_dynarray

all: $(NAME1) $(NAME2)

part_1: $(NAME1)
	@./$(NAME1)

$(NAME1): $(NAME1).c $(LIBFT) $(LIBARRAYS)
	@cc $(NAME1).c $(FLAGS) -o $(NAME1)

$(LIBFT):
	@make -C ../libft/

$(LIBARRAYS):
	@make -C ../dynamic_arrays/

clean:
	rm -f $(NAME1) $(NAME2)

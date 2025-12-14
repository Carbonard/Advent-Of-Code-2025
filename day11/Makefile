.PHONY: all fclean

NAME1 = part_1_count_paths

NAME2 = part_2_count_specific_paths

LIBFT = ../libft/libft.a

LIBARRAYS = ../dynamic_arrays/libft_dynarray.a

FLAGS = -Wall -Werror -Wextra -O3 -I ../libft/ -L ../libft/ -lft -I ../dynamic_arrays/src -L ../dynamic_arrays/ -lft_dynarray

all: $(NAME1) $(NAME2)

part_1: $(NAME1)
	@./$(NAME1)

$(NAME1): $(NAME1).c $(LIBFT) $(LIBARRAYS)
	@cc $(NAME1).c $(FLAGS) -o $(NAME1)

part_2: $(NAME2)
	@./$(NAME2)

$(NAME2): $(NAME2).c $(LIBFT) $(LIBARRAYS)
	@cc $(NAME2).c $(FLAGS) -o $(NAME2)

$(LIBFT):
	@make -C ../libft/

$(LIBARRAYS):
	@make -C ../dynamic_arrays/

clean:
	rm -f $(NAME1) $(NAME2)


NAME = Minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -g
# -fsanitize=address
INCLUDE = minishell.h

SRC =	obj/Minishell.c\
		obj/is_func.c\
		obj/ft_split.c\
		obj/env.c\
		obj/libft.c\
		obj/parsing.c\
		obj/parsing_creat.c\
		obj/execution_2.c\
		obj/implement.c\
		obj/export.c\
		obj/free_or_exit.c\
		obj/ft_error.c
		# obj/linked_list_totabstruct.c\




OBJ = $(SRC:.c=.o)

mkdir = mkdir -p

dir = obj

#  //// should i use object file to compil //*/**/

all: $(NAME)

$(NAME): ${dir} $(OBJ)  $(INCLUDE)
	$(CC) $(FLAGS) $(OBJ) -lreadline -o $(NAME) 


obj/%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

${dir} : 
	@${mkdir} ${dir}


clean:
	rm -rf obj
fclean:
	rm -rf $(NAME) obj

re: fclean all

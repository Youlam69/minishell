
NAME = minishell

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
		obj/redirection.c\
		obj/cd_func.c\
		obj/check_inparsing.c\
		obj/joinpath.c\
		obj/ft_error.c\
		obj/env_plus.c\
		obj/env_two.c\
		obj/exec.c\
		obj/export_plus.c\
		obj/free_or_exit_two.c\
		obj/ft_split_two.c\
		obj/implement_two.c\
		obj/extra_main.c\
		obj/parsing_two.c\
		obj/parsing_one.c\
		obj/parsing_creat_two.c\
		obj/libft_two.c\
		obj/libft_one.c\
		obj/redirection_one.c\
		obj/redirection_two.c


OBJ = $(SRC:.c=.o)

mkdir = mkdir -p
RDDIR = /goinfre/ylamraou/homebrew/opt/readline

dir = obj

#  //// should i use object file to compil //*/**/

all: $(NAME)

$(NAME): ${dir} $(OBJ)  $(INCLUDE)
	$(CC) $(FLAGS) -lreadline -I $(RDDIR)/include -L $(RDDIR)/lib $(OBJ) -o $(NAME) 


obj/%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) -I $(RDDIR)/include -c $< -o $@

${dir} : 
	@${mkdir} ${dir}


clean:
	rm -rf obj
fclean:
	rm -rf $(NAME) obj

re: fclean all

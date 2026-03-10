NAME	=	minishell

CC		=	cc
FLAG	=	-Wall -Wextra -Werror

DIRLIB	=	./libft/
FILELIB	=	libft.a
NAMELFT	=	$(addprefix $(DIRLIB), $(FILELIB))

SRC_DIR	=	src/
OBJ_DIR	=	obj/
INCLUDE	=	-I ./libft

DEF_COLOR	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

FILES	=	main tokenize create_cmd expand expand2 heredoc free_funcs signals \
			utils_builtin other_utils exec exec2 exec_builtin find_cmd ft_cd \
			ft_echo ft_env ft_exit ft_export ft_export2 export_utils ft_pwd ft_unset \
			quote_and_pipe utils_cmd_tok print_error

OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF	=	.cache_exits

$(OBJF) :
	@mkdir -p $(OBJ_DIR)

vpath %.c $(SRC_DIR) $(SRC_DIR)parsing $(SRC_DIR)utils $(SRC_DIR)exec $(SRC_DIR)builtin

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(DIRLIB)
	$(CC) $(FLAG) $(OBJS) $(NAMELFT) -lreadline $(INCLUDE) -o $(NAME)
	@echo -e "$(GREEN)Minishell Compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o : %.c Makefile | $(OBJF)
	$(CC) $(FLAG) $(INCLUDE) -c $< -o $@

clean :
	@ make clean -sC $(DIRLIB)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJF)
	@echo -e "$(MAGENTA)Minishell objects cleaned !$(DEF_COLOR)"

fclean : clean
	@ make fclean -sC $(DIRLIB)
	@rm -rf $(NAME)
	@rm -rf $(NAME_B)
	@echo -e "$(YELLOW)Minishell cleaned !$(DEF_COLOR)"

re : fclean all
	@echo -e "$(GREEN)Cleaned and rebuilt !$(DEF_COLOR)"

.PHONY : all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 10:47:51 by albaud            #+#    #+#              #
#    Updated: 2023/04/03 14:55:18 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
FILES	= args/args.c args/args_utils.c bonus/levels.c bonus/wildcards.c builtins/builtins.c\
			builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_export.c builtins/ft_pwd.c\
			builtins/ft_unset.c errors/parse_error.c global/execute.c global/ft_mf.c global/main.c global/pipi.c\
			injection/fd_fd_injection.c injection/fd_injection.c injection/filename_injection.c list/string_list.c\
			list/vars_list.c parser/parser.c parser/parser_handler.c signals/signals.c vars/vars.c bonus/ft_glob.c\
			bonus/ft_count_dir.c vars/export_manager.c bonus/priorities.c
OBJS 	= ${FILES:.c=.o}
INCL	= ./
LIB		= koflibc/libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

.c.o 	:
		${CC} -g ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
		gcc -g -Wall -Werror -Wextra ${OBJS} ${LIB} -o ${NAME} -lreadline

c:
	find *.c */*.c | tr '\n' ' '

recompile :
	make re -C koflibc
	make re

re : fclean all

fclean : clean
	rm -f $(NAME)

clean :
	rm -f $(OBJS)

run: all
	./minishell

.PHONY : all c recompile re clean fclean run
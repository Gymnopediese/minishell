# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 11:18:52 by albaud            #+#    #+#              #
#    Updated: 2022/12/09 10:39:45 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
FILES	= args/args.c args/args_utils.c bonus/levels.c bonus/wildcards.c builtins/builtins.c builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_export.c builtins/ft_pwd.c builtins/ft_unset.c errors/parse_error.c global/execute.c global/main.c global/pipi.c injection/fd_fd_injection.c injection/fd_injection.c injection/filename_injection.c list/string_list.c list/vars_list.c parser/parser.c parser/parser_handler.c signals/signals.c vars/vars.c
INCL	= ./
LIB		= koflibc/libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
SAN		= 

.c.o 	:
		${CC} -g ${CFLAGS} -c $< -o ${<:.c=.o}
		

all: ${NAME}

${NAME}: ${OBJS}
		gcc -g -Wall -Werror -Wextra -lreadline ${SAN} ${OBJS} ${LIB} -o ${NAME} 

c:
	find *.c */*.c | tr '\n' ' '

clean :
	rm -f $(OBJS)

run: all
	./minishell
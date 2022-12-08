# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ben <ben@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 11:18:52 by albaud            #+#    #+#              #
#    Updated: 2022/12/08 16:05:47 by ben              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
FILES	= args.c execute.c injectors.c main.c pipi.c vars.c bonus/levels.c bonus/wildcards.c builtins/builtins.c builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_export.c builtins/ft_pwd.c builtins/ft_unset.c errors/parse_error.c list/string_list.c list/vars_list.c parser/parser.c parser/parser_handler.c signals/signals.c
OBJS 	= ${FILES:.c=.o}
INCL	= ./
LIB		= koflibc/libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
SAN		= 
.c.o 	:
		${CC} -g ${CFLAGS} -c $< -o ${<:.c=.o} -lreadline
		

all: ${NAME}

${NAME}: ${OBJS}
		gcc -g -Wall -Werror -Wextra ${SAN} ${OBJS} ${LIB} -o ${NAME} -lreadline

c:
	find *.c */*.c | tr '\n' ' '

clean :
	rm -f $(OBJS)

run: all
	./minishell
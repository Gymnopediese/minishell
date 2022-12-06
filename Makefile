# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 11:18:52 by albaud            #+#    #+#              #
#    Updated: 2022/12/06 14:46:01 by bphilago         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
FILES	= execute.c main.c list/string_list.c vars.c list/vars_list.c parser/parser.c parser/parser_handler.c signals/signals.c
OBJS 	= ${FILES:.c=.o}
INCL	= ./
LIB		= koflibc/libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

.c.o 	:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
		

all: ${NAME}

${NAME}: ${OBJS}
		gcc -Wall -Werror -Wextra -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include ${OBJS} ${LIB} -o ${NAME} 

c:	
	find *.c */*.c | tr '\n' ' '

clean :
	rm -f $(OBJS)

run: all
	./minishell
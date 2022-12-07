# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 11:18:52 by albaud            #+#    #+#              #
#    Updated: 2022/12/07 10:04:41 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
FILE	= *.c
OBJS 	= ${FILES:.c=.o}
INCL	= ./
LIB		= koflibc/libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
CCC 	= $(wildcard */*.c) $(wildcard *.c)
C		= ${CCC:*/*=*\\/*}

.c.o 	:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
		

all: ${NAME}

${NAME}: ${OBJS}
		gcc -Wall -Werror -Wextra -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include ${OBJS} ${LIB} -o ${NAME} 

c++:
	sed '14s/.*/FILE = ${C}/' Makefile > test
	cat test > Makefile



clean :
	rm -f $(OBJS)

run: all
	./minishell
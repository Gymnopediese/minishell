# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 18:46:11 by albaud            #+#    #+#              #
#    Updated: 2023/04/04 13:33:10 by bphilago         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 	= $(wildcard */*.c) $(wildcard */*/*.c)
OBJS 	= ${SRCS:.c=.o}
NAME 	= libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

.c.o 	:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
		
all 	: $(NAME)

$(NAME)	: ${OBJS}
		ar rcs ${NAME} ${OBJS}

clean	:
		rm -f ${OBJS}

fclean	:	clean
		rm -f ${NAME}

re		: fclean all

push	:
		git add *
		git commit -m save
		git push
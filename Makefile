# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgankhuy <dgankhuy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/25 11:30:49 by duk               #+#    #+#              #
#    Updated: 2026/10/29 14:24:45 by dgankhuy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

NAME = libftprintf.a

SRC = ft_printf.c \
      ft_printf_utils.c

OBJ = ${SRC:.c=.o}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	ar rcs $(NAME) ${OBJ}

all: ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}
	
re: fclean all

.PHONY: all clean fclean re

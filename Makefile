# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 12:07:13 by zwong             #+#    #+#              #
#    Updated: 2022/09/01 12:21:58 by zwong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

HEADER	= pipex.h

SRC		= pipex.c utils.c
OBJS	= ${SRC:c=o}

all: ${NAME}

${NAME}: ${OBJS}
	@echo "Compiling pipex..."
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS}
	@echo "DONE!"

%.o: %.c
	@echo "Generating pipex objects..."
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

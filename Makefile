# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 12:07:13 by zwong             #+#    #+#              #
#    Updated: 2022/09/22 11:12:31 by zwong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
INCLUDES	= ./mandatory/includes

SRCS		= pipex.c helper.c utils.c
SRCS_PATH	= $(addprefix mandatory/srcs/, ${SRCS})
OBJS		= ${SRCS_PATH:.c=.o}

LIBFT_DIR	= libft/
LIBFT_LIB	= libft.a

#COMMANDS

all: ${NAME}

${LIBFT_LIB}:
	@make bonus -C ${LIBFT_DIR}

${NAME}: ${LIBFT_LIB} ${OBJS}
	@echo -e "${YELLOW}COMPILING PIPEX...${DEFAULT}"
	@${CC} ${CFLAGS} -I${INCLUDES} ${OBJS} ${LIBFT_DIR}/${LIBFT_LIB} -o ${NAME}
	@echo -e "${GREEN}COMPILE DONE!${DEFAULT}"

clean:
	@echo -e "${YELLOW}CLEANING FILES...${DEFAULT}"
	@make clean -C ${LIBFT_DIR}
	@rm -rf ${OBJS}
	@echo -e "${GREEN}CLEANING DONE!${DEFAULT}"

fclean: clean
	@echo -e "${YELLOW}CLEANING FILES...${DEFAULT}"
	@make fclean -C ${LIBFT_DIR}
	@rm -rf ${NAME}
	@echo -e "${GREEN}CLEANING DONE!${DEFAULT}"

re: fclean all

.PHONY:	all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
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
INCLUDES_M	= ./mandatory/includes

SRCS		= pipex.c helper.c utils.c
SRCS_PREFIX	= $(addprefix mandatory/srcs/, ${SRCS})

LIBFT_DIR	= libft/
LIBFT_LIB	= libft.a

all: ${NAME}

${LIBFT_LIB}:
	@make bonus -C ${LIBFT_DIR}

${NAME}: ${LIBFT_LIB}
	@echo "COMPILING PIPEX..."
	@${CC} ${CFLAGS} -I${INCLUDES_M} ${SRCS_PREFIX} ${LIBFT_DIR}/${LIBFT_LIB} -o ${NAME}
	@echo "DONE!"

# ${NAME}: ${OBJS}
# 	@echo "Compiling pipex..."
# 	@${CC} ${CFLAGS} -o ${NAME} ${OBJS}
# 	@echo "DONE!"

# %.o: %.c
# 	@echo "Generating pipex objects..."
# 	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@make fclean -C ${LIBFT_DIR}

fclean: clean
	@rm -rf ${NAME}

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: EugenieFrancon <EugenieFrancon@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/18 22:02:30 by EugenieFr         #+#    #+#              #
#    Updated: 2021/09/27 18:53:47 by EugenieFran      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

SRCS_DIR		= ./srcs

SRCS			= main.c \
				setup_data.c \
				init_philo.c \
				parse_arguments.c \
				run_philo.c \
				live.c \
				philo_activity.c \
				display_status.c \
				supervise_life_philo.c \
				handle_time.c \
				cleanup.c \
				utils_philo.c \
				libft.c

OBJS_DIR		= ./objs

OBJS			= ${addprefix ${OBJS_DIR}/, ${SRCS:.c=.o}}

CC				= clang

CFLAGS			= -Wall -Wextra -Werror -pthread -I${INCLUDE} -g #-fsanitize=thread

RM				= rm -rf

INCLUDE			= includes

RESET			= \033[0m
GREEN			= \033[32m
BLUE			= \033[34m
YELLOW			= \033[33m

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
		@mkdir -p ${OBJS_DIR}
		@${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
		@echo "${YELLOW}Starting compilation philosophers...${RESET}"
		@${CC} ${OBJS} ${CFLAGS} -o ${NAME}
		@echo "${GREEN}PHILOSOPHERS : compiled !${RESET}"

all:		${NAME}

clean:
		@${RM} ${OBJS_DIR}
		@echo "${BLUE}PHILOSOPHERS : objects removed${RESET}"

fclean:		clean
		@${RM} ${NAME}
		@echo "${BLUE}PHILOSOPHERS : philo removed${RESET}"

re:			fclean all

.PHONY:		all bonus clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/18 22:02:30 by EugenieFr         #+#    #+#              #
#    Updated: 2022/01/12 20:21:08 by efrancon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo_bonus

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
				utils.c \
				libft.c \
				libft_2.c

OBJS_DIR		= ./objs

OBJS			= ${addprefix ${OBJS_DIR}/, ${SRCS:.c=.o}}

DEP				= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.d))

CC				= clang

CFLAGS			= -Wall -Wextra -Werror -pthread -MMD -MP -I${INCLUDE} -g3 #-fsanitize=thread

RM				= rm -rf

INCLUDE			= includes

RESET			= \033[0m
GREEN			= \033[32m
BLUE			= \033[34m
YELLOW			= \033[33m


${NAME}:	${OBJS}
		@${CC} ${OBJS} ${CFLAGS} -o ${NAME}
		@echo "${GREEN}BONUS PHILOSOPHERS : compiled !${RESET}"

-include $(DEP)
${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
		@mkdir -p ${OBJS_DIR}
		@${CC} ${CFLAGS} -c $< -o $@
		@echo "$(BLUE)clang $(RESET)$(notdir $@)"

all:		${NAME}

clean:
		@${RM} ${OBJS_DIR}
		@echo "${YELLOW}objects removed${RESET}"

fclean:		clean
		@${RM} ${NAME}
		@echo "${YELLOW}philo_bonus removed${RESET}"

re:			fclean all

.PHONY:		all clean fclean re

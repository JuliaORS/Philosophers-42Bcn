# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/03 17:22:44 by julolle-          #+#    #+#              #
#    Updated: 2023/08/03 17:22:44 by julolle-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

HEADER      := philo.h

SRC_DIR		:= srcs
SRCS 		:= philosophers.c check_args.c init_vars.c create_threads.c \
				do_routine.c utils.c print_messages.c check_death.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

OBJS		:= $(SRCS:.c=.o)
DEPS		:= $(OBJS:.o=.d)

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD

RM			:= rm -f

#Implicit Method
%.o: %.c	Makefile
	$(CC) $(CFLAGS) ${INCLUDE} -c $< -o $@

# My methods
all:	$(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

-include $(DEPS)

# Phony
.PHONY: all clean fclean re

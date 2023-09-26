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

NAME		:= philo_bonus

HEADER      := philo_bonus.h

SRC_DIR		:= srcs
SRCS 		:= philosophers.c check_args.c create_process.c utils.c do_routine.c 
				
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

OBJS		:= $(SRCS:.c=.o)
DEPS		:= $(OBJS:.o=.d)

CC			:= gcc -fsanitize=thread -g 
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

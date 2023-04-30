# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 17:16:37 by jhwang2           #+#    #+#              #
#    Updated: 2023/04/30 04:21:03 by jhwang2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO		=	philo
NAME		=	$(PHILO)
CC			=	cc
RM			=	rm -rf
LIBC		=	ar rcs
CFLAGS		=	-Wall -Wextra -Werror
SRCS		=	main.c \
				init.c \
				malloc.c \
				close_sem.c \
				start_philo.c \
				do_routine1.c \
				do_routine2.c \
				take_fork.c \
				philo_function1.c \
				philo_function2.c
OBJS		=	${SRCS:.c=.o}

all :
	@$(MAKE) -j6 $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re :
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re

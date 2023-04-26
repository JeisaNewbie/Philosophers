# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 20:19:22 by sechung           #+#    #+#              #
#    Updated: 2023/04/25 16:00:08 by ahkiler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO		=	philo
PHILO_BONUS	=	philo_bonus
NAME		=	$(PHILO) $(PHILO_BONUS)
CC			=	cc
RM			=	rm -rf
LIBC		=	ar rcs
CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=thread
SRCDIR		=	src
INCDIR		=	./include
INCS		=	-I $(INCDIR)
SRCS		=	main.c \
				init.c \
				malloc.c \
				start_philo.c \
				do_routine1.c \
				do_routine2.c \
				take_fork.c \
				philo_function1.c \
				philo_function2.c
BONUS_SRCS	=	main_bonus.c \
				init_bonus.c \
				fork_bonus.c \
				do_routine1_bonus.c \
				do_routine2_bonus.c \
				philo_function1_bonus.c \
				philo_function2_bonus.c \
				philo_function3_bonus.c \
				wait_and_kill_bonus.c
OBJS		=	${SRCS:.c=.o}
BONUS_OBJS	=	${BONUS_SRCS:.c=.o}

ifdef WITH_BONUS
	NAME = $(PHILO_BONUS)
	OBJECTS = $(BONUS_OBJS)
else
	NAME = $(PHILO)
	OBJECTS = $(OBJS)
endif

all : $(NAME)
	@$(MAKE) -j6 $(NAME)

$(NAME) : $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

bonus :
	@$(MAKE) WITH_BONUS=1 all

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean :
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean : clean
	@$(RM) $(PHILO) $(PHILO_BONUS)

re :
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re bonus

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 20:19:22 by sechung           #+#    #+#              #
#    Updated: 2023/04/27 15:13:57 by jhwang2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO		=	philo
PHILO_BONUS	=	philo_bonus
NAME		=	$(PHILO) $(PHILO_BONUS)
CC			=	cc
RM			=	rm -rf
LIBC		=	ar rcs
CFLAGS		=	-Wall -Wextra -Werror
SRCDIR		=	src
INCDIR		=	./include
INCS		=	-I $(INCDIR)
SRCS		=	main.c \
				init.c \
				malloc.c \
				do_routine1.c \
				do_routine2.c \
				fork1.c \
				fork2.c \
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

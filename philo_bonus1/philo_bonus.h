/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:13:55 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/05 14:41:47 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>

typedef struct s_sem
{
	sem_t			*forks;
	sem_t			*sem_print;
	sem_t			*sem_eaten;
}	t_sem;

typedef struct s_philo
{
	sem_t			*wait;
	u_int64_t		usec_before;
	u_int64_t		time_to_die_origin;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				num_of_time_to_eat;
	int				eaten;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	t_sem			*sem;
	pid_t			*philos;
	pid_t			pid;
	u_int64_t		time_to_start;
	char			**argv;
	int				num_of_philos;
	int				num_of_proc_ended;
	int				flag;
	int				id;
}	t_data;

//---------------------------main.c
int			check_vaild(int argc, char **argv);
int			check_argument(char **argv);
int			creat_sem(t_data *philos);
//---------------------------wait_and_kill.c

void		wait_and_kill(t_data *philos);
int			wait_proc(t_data *philos);
int			check_dead(t_data *philos, int status, int error);
void		*check_eaten(void *arg);
int			kill_proc(t_data *philos, int i);
void		check_time(t_philo *philo);
//---------------------------init.c

int			init_philos(t_data *philos, char **argv);
int			init_base(t_data *philos, char **argv);
void		init_philo(t_data *philos, t_philo *philo, char **argv);
void		init_time(t_data *philos);

//---------------------------do_routine.c

void		do_routine(t_data *philos);
void		do_routine_odd(t_data *philos);
int			thinking(t_data *philos);
int			thinking_odd(t_data *philos);
int			sleeping(t_data *philos);
int			eating(t_data *philos);
void		take_fork(t_data *philos);
void		put_fork(t_data *philos);

//---------------------------fork.c

int			fork_proc(t_data *philos);
int			fork_child(t_data *philos);
int			start(t_data *philos);
int			start_philo(t_data *philos, int i);

//---------------------------do_odd & utils.c

//---------------------------philo_function 1 & 2.c

void		print_status(t_data *philos, t_philo *philo, int id, char *str);
void		p_usleep(t_data *philos, t_philo *philo, u_int64_t time);
int			close_sem(t_data *philos, int i);
u_int64_t	get_gtd(void);
void		*p_calloc(size_t count, size_t size);
void		p_bzero(void *dest, size_t size);
int			p_atoi(const char *str);
size_t		p_strlen(const char *str);
size_t		p_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_itoa(int n);
void		ft_putnbr(char *s, int n, int len_n);
void		recursion(char *s, int n, int len_n);
int			ft_len(int n);

#endif
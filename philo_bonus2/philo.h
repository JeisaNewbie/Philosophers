/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:23:03 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/30 04:19:57 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	sem_t			*sem_setting;
	sem_t			*s_one;
	sem_t			*s_two;
	sem_t			*s_three;
}	t_sem;

typedef struct s_data
{
	t_sem			*sem;
	u_int64_t		time_to_start;
	pid_t			*philos;
	pid_t			pid;
	char			**argv;
	int				num_of_philos;
	int				num_of_philos_ended;
	int				num_of_philos_eaten;
	int				flag;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	u_int64_t		usec_before;
	u_int64_t		time_to_die_origin;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				num_of_time_to_eat;
	int				eaten;
	int				id;
}	t_philo;

//---------------------------main.c
void		start_philo(t_philo **philos, t_data *data);
void		wait_pth(t_data *data);
//---------------------------init.c

t_philo		**init_philos(t_data *data, char **argv);
int			init_base(t_data *data, char **argv);
void		init_philo(t_philo *philos, t_data *data, int id);
void		init_time(t_data *data);
int			creat_sem(t_data *data);
//---------------------------do_routine.c
void		do_routine(t_data *data, t_philo *philo);
void		thinking(t_data *data, t_philo *philo);
void		sleeping(t_data *data, t_philo *philo);
void		eating(t_data *data, t_philo *philo);
void		eating_all(t_data *data);
int			p_usleep(t_data *data, t_philo *philo, u_int64_t time);
u_int64_t	get_gtd(void);

//---------------------------start_philo.c
void		create_pth(t_philo **philos, t_data *data, int i);
void		*start_pth(void *arg);
void		waiting(t_philo *philo, t_data *data);
void		start_philo(t_philo **philos, t_data *data);
void		start_proc(t_data *data, int i);
//---------------------------fork.c

void		take_fork(t_data *data, t_philo *philo);
void		put_fork(t_data *data);

int			fork_proc(t_data *data);
int			fork_child(t_data *data);
int			start(t_data *data);

//---------------------------malloc.c
t_philo		**malloc_all(t_data *data);
int			malloc_mutex(t_data *data);
int			malloc_forks(t_data *data);
int			malloc_fork_mutex(t_data *data);
t_philo		**malloc_philo(t_data *data);
//---------------------------philo_function 1 & 2.c
int			check_vaild(int argc, char **argv);
int			check_argument(char **argv);
void		print_status(t_data *data, t_philo *philo, int id, char *str);
void		rm_mutex_all(t_data *data, int end);
void		*p_calloc(size_t count, size_t size);
void		p_bzero(void *dest, size_t size);
int			p_atoi(const char *str);
size_t		p_strlen(const char *str);
size_t		p_strlcat(char *dst, const char *src, size_t dstsize);

//---------------------------close_sem.c

int			close_sem(t_data *data, int i);
void		close_sem_all(t_data *data, int i);

void		wait_proc(t_data *data);
void		kill_proc(t_data *data);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:23:03 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/25 15:58:43 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_philo
{
	struct timeval	tv;
	u_int64_t		usec_before;
	u_int64_t		time_to_die_origin;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				num_of_time_to_eat;
	int				eaten;
}	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	setting_mutex;
}	t_mutex;

typedef struct s_data
{
	t_philo			*philo;
	t_mutex			*mutex;
	u_int64_t		time_to_start;
	char			**argv;
	int				*forks;
	int				end;
	int				num_of_philos;
	int				num_of_philos_eaten;
	int				eaten_philos;
	int				flag;
	int				target;
	int				id;
}	t_data;

//---------------------------main.c
void		monitoring_pthread(t_data *philos);
int			wait_pth(t_data *philos, t_philo *philo);
//---------------------------init.c

int			init_philos(t_data *philos, char **argv);
void		init_base(t_data *philos, char **argv);
void		init_philo(t_data *philos, t_philo *philo, int *id, int *left_id);
void		init_time(t_data *philos, t_philo *philo);

//---------------------------do_routine.c
void		do_routine(t_data *philos, t_philo *philo, int id, int left_id);
int			thinking(t_data *philos, t_philo *philo, int id);
int			sleeping(t_data *philos, t_philo *philo, int id);
int			eating(t_data *philos, t_philo *philo, int id, int left_id);
int			eating_all(t_data *philos);
int			check_died(t_data *philos, t_philo *philo, int id, int recover);
int			p_usleep(t_data *philos, t_philo *philo, int id, u_int64_t time);
u_int64_t	get_gtd(t_philo *philo);

//---------------------------start_philo.c
void		start_philo(t_data *philos);
void		create_pth(t_data *philos, int i);
void		*start_pth(void *arg);
void		end_pth(t_data *philos);

//---------------------------fork.c

int			take_fork(t_data *philos, t_philo *philo, int id, int left_id);
void		put_forks(t_data *philos, int id, int left_id);
void		take_forks(t_data *philos, t_philo *philo, int id, int left_id);

//---------------------------malloc.c
int			malloc_all(t_data *philos);
int			malloc_mutex(t_data *philos);
int			malloc_forks(t_data *philos);
int			malloc_fork_mutex(t_data *philos);
//---------------------------philo_function 1 & 2.c
int			check_vaild(int argc, char **argv);
int			check_argument(char **argv);
int			print_status(t_data *philos, t_philo *philo, int id, int flag);
void		rm_mutex_all(t_data *philos, int end);
void		*p_calloc(size_t count, size_t size);
void		p_bzero(void *dest, size_t size);
int			p_atoi(const char *str);
size_t		p_strlen(const char *str);
size_t		p_strlcat(char *dst, const char *src, size_t dstsize);

#endif
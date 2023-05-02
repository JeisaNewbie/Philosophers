/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:23:03 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/02 13:13:03 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_mutex
{
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	setting_mutex;
	pthread_mutex_t	end_mutex;
}	t_mutex;

typedef struct s_data
{
	t_mutex			*mutex;
	u_int64_t		time_to_start;
	char			**argv;
	int				*forks;
	int				end;
	int				num_of_philos;
	int				num_of_philos_eaten;
	int				num_of_philos_ended;
}	t_data;

typedef struct s_philo
{
	struct timeval	tv;
	t_data			*data;
	u_int64_t		usec_before;
	u_int64_t		time_to_die_origin;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				num_of_time_to_eat;
	int				eaten;
	int				id;
	int				left_id;
}	t_philo;

void		start_philo(t_philo **philos, t_data *data);
void		monitoring_pthread(t_data *data);
void		wait_pth(t_data *data, int *error);
void		free_all(t_philo **philos, t_data *data);
t_philo		**init_philos(t_data *data, char **argv);
void		init_base(t_data *data, char **argv);
void		init_philo(t_philo *philos, t_data *data, int id);
void		init_time(t_data *data);
void		do_routine(t_philo *philo, t_data *data, int id, int left_id);
int			thinking(t_data *data, t_philo *philo, int id);
int			sleeping(t_data *data, t_philo *philo, int id);
int			eating(t_data *data, t_philo *philo, int id, int left_id);
void		eating_all(t_data *data);
int			p_usleep(t_data *data, t_philo *philo, int id, u_int64_t time);
u_int64_t	get_gtd(void);
void		create_pth(t_philo **philos, t_data *data, int i);
void		*start_pth(void *arg);
int			end_pth(t_data *data);
void		add_philo_ended(t_philo *philo);
int			take_fork(t_data *data, t_philo *philo, int id, int left_id);
void		take_forks(t_data *data, int id, int left_id);
int			put_forks(t_data *data, int id, int left_id);
t_philo		**malloc_all(t_data *data);
int			malloc_mutex(t_data *data);
int			malloc_forks(t_data *data);
int			malloc_fork_mutex(t_data *data);
t_philo		**malloc_philo(t_data *data);
int			check_vaild(int argc, char **argv);
int			check_argument(char **argv);
void		print_status(t_data *data, t_philo *philo, int id, char *str);
void		rm_mutex_all(t_data *data, int end);
void		*p_calloc(size_t count, size_t size);
void		p_bzero(void *dest, size_t size);
int			p_atoi(const char *str);
size_t		p_strlen(const char *str);
size_t		p_strlcat(char *dst, const char *src, size_t dstsize);

#endif
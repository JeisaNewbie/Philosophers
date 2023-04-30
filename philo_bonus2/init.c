/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:40 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/30 04:20:33 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philos(t_data *data, char **argv)
{
	if (!init_base (data, argv))
		return (0);
	if (!creat_sem (data))
		return (0);
	return (malloc_all (data));
}

int	init_base(t_data *data, char **argv)
{
	data->num_of_philos = p_atoi (argv[1]);
	data->philos = (pid_t *)p_calloc (data->num_of_philos, sizeof (pid_t));
	if (data->philos == NULL)
		return (0);
	data->argv = argv;
	data->num_of_philos_ended = 0;
	data->num_of_philos_eaten = 0;
	data->flag = -1;
	return (1);
}

int	creat_sem(t_data *data)
{
	data->sem->forks = sem_open ("forks", O_CREAT, 0666, data->num_of_philos);
	if (data->sem->forks == SEM_FAILED)
		return (close_sem (data, 1));
	sem_unlink ("forks");
	data->sem->sem_print = sem_open ("sem_print", O_CREAT, 0666, 1);
	if (data->sem->sem_print == SEM_FAILED)
		return (close_sem (data, 2));
	sem_unlink ("sem_print");
	data->sem->sem_setting = sem_open ("sem_setting", O_CREAT, 0666, 1);
	if (data->sem->sem_setting == SEM_FAILED)
		return (close_sem (data, 3));
	sem_unlink ("sem_setting");
	data->sem->s_one = sem_open ("s_one", O_CREAT, 0666, 0);
	if (data->sem->s_one == SEM_FAILED)
		return (close_sem (data, 4));
	sem_unlink ("s_one");
	data->sem->s_two = sem_open ("s_two", O_CREAT, 0666, 0);
	if (data->sem->s_two == SEM_FAILED)
		return (close_sem (data, 5));
	sem_unlink ("s_two");
	data->sem->s_three = sem_open ("s_three", O_CREAT, 0666, 0);
	if (data->sem->s_three == SEM_FAILED)
		return (close_sem (data, 6));
	sem_unlink ("s_three");
	return (1);
}

void	init_philo(t_philo *philos, t_data *data, int id)
{
	philos->id = id;
	philos->data = data;
	philos->eaten = 0;
	philos->time_to_die = 0;
	philos->time_to_die_origin = (u_int64_t)p_atoi (data->argv[2]);
	philos->time_to_eat = (u_int64_t)p_atoi (data->argv[3]);
	philos->time_to_sleep = (u_int64_t)p_atoi (data->argv[4]);
	if (data->argv[5] != NULL)
		philos->num_of_time_to_eat = p_atoi (data->argv[5]);
	else
		philos->num_of_time_to_eat = -1;
}

void	init_time(t_data *data)
{
	data->time_to_start = get_gtd ();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 20:16:49 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/30 03:56:41 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_pth(t_philo **philos, t_data *data, int i)
{
	pthread_t	philo;

	while (i < data->num_of_philos)
	{
		pthread_create (&philo, 0, start_pth, (void *)philos[i]);
		pthread_detach (philo);
		i += (data->num_of_philos & 1) + 2;
	}
}

void	*start_pth(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	pid_t	pid;

	philo = (t_philo *)arg;
	data = philo->data;
	pid = fork ();
	if (pid > 0)
		data->philos[philo->id] = pid;
	if (pid < 0 || pid > 0)
		return (0);
	waiting (philo, data);
	do_routine (data, philo);
	return (0);
}

void	waiting(t_philo *philo, t_data *data)
{
	if (philo->id % (data->num_of_philos & 1) + 2 == 0)
		sem_wait (data->sem->s_one);
	else if (philo->id % (data->num_of_philos & 1) + 2 == 1)
		sem_wait (data->sem->s_two);
	else if (philo->id % (data->num_of_philos & 1) + 2 == 2)
		sem_wait (data->sem->s_three);
	philo->usec_before = data->time_to_start;
}

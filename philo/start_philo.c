/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 20:16:49 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/29 21:57:45 by jhwang2          ###   ########.fr       */
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
		if (i == 0)
		{
			pthread_mutex_lock (&data->mutex->setting_mutex);
			init_time (data);
			pthread_mutex_unlock (&data->mutex->setting_mutex);
		}
		i += (data->num_of_philos & 1) + 2;
	}
}

void	*start_pth(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock (&data->mutex->setting_mutex);
	philo->usec_before = data->time_to_start;
	pthread_mutex_unlock (&data->mutex->setting_mutex);
	do_routine (philo, data, philo->id, philo->left_id);
	add_philo_ended (philo);
	return (0);
}

int	end_pth(t_data *data)
{
	pthread_mutex_lock (&data->mutex->setting_mutex);
	if (data->end > 0)
	{
		pthread_mutex_unlock (&data->mutex->setting_mutex);
		return (0);
	}
	pthread_mutex_unlock (&data->mutex->setting_mutex);
	return (1);
}

void	add_philo_ended(t_philo *philo)
{
	pthread_mutex_lock (&philo->data->mutex->end_mutex);
	philo->data->num_of_philos_ended++;
	pthread_mutex_unlock (&philo->data->mutex->end_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork_odd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:43 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/03 14:07:08 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork_odd(t_data *data, t_philo *philo, int id, int left_id)
{
	take_forks_odd (data, id, left_id);
	philo->time_to_die += get_gtd () - philo->usec_before;
	if (philo->time_to_die_origin <= philo->time_to_die)
	{
		pthread_mutex_lock (&data->mutex->setting_mutex);
		if (data->end == 0)
			data->end = id + 1;
		pthread_mutex_unlock (&data->mutex->setting_mutex);
		put_forks_odd (data, id, left_id);
		return (1);
	}
	if (!end_pth (data))
		return (put_forks_odd (data, id, left_id));
	print_takef (data, philo, id, "has taken a fork");
	return (0);
}

void	take_forks_odd(t_data *data, int id, int left_id)
{
	if (id == data->num_of_philos - 1)
	{
		pthread_mutex_lock (&data->mutex->fork_mutex[id]);
		usleep (500);
		pthread_mutex_lock (&data->mutex->fork_mutex[left_id]);
	}
	else if (id % 2 == 1)
	{
		pthread_mutex_lock (&data->mutex->fork_mutex[left_id]);
		pthread_mutex_lock (&data->mutex->fork_mutex[id]);
	}
	else if (id % 2 == 0)
	{
		pthread_mutex_lock (&data->mutex->fork_mutex[id]);
		pthread_mutex_lock (&data->mutex->fork_mutex[left_id]);
	}
	data->forks[id] = id;
	data->forks[left_id] = id;
}

int	put_forks_odd(t_data *data, int id, int left_id)
{
	data->forks[id] = -1;
	data->forks[left_id] = -1;
	pthread_mutex_unlock (&data->mutex->fork_mutex[id]);
	pthread_mutex_unlock (&data->mutex->fork_mutex[left_id]);
	return (1);
}

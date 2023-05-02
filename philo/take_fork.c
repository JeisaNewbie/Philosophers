/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:43 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/02 13:10:11 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_data *data, t_philo *philo, int id, int left_id)
{
	take_forks (data, id, left_id);
	philo->time_to_die += get_gtd () - philo->usec_before;
	if (philo->time_to_die_origin <= philo->time_to_die)
	{
		pthread_mutex_lock (&data->mutex->setting_mutex);
		if (data->end == 0)
			data->end = id + 1;
		pthread_mutex_unlock (&data->mutex->setting_mutex);
		put_forks (data, id, left_id);
		return (1);
	}
	print_status (data, philo, id, "has taken a fork");
	if (id == left_id)
		return (p_usleep (data, philo, id, philo->time_to_die_origin * 2));
	data->forks[left_id] = id;
	if (!end_pth (data))
		return (put_forks (data, id, left_id));
	print_status (data, philo, id, "has taken a fork");
	return (0);
}

void	take_forks(t_data *data, int id, int left_id)
{
	int	denom;

	denom = (data->num_of_philos & 1) + 2;
	if (id % denom == 0 || id % denom == 2)
	{
		pthread_mutex_lock (&data->mutex->fork_mutex[id]);
		if (id == left_id)
		{
			data->forks[id] = id;
			pthread_mutex_unlock (&data->mutex->fork_mutex[id]);
			return ;
		}
		pthread_mutex_lock (&data->mutex->fork_mutex[left_id]);
	}
	else
	{
		pthread_mutex_lock (&data->mutex->fork_mutex[left_id]);
		pthread_mutex_lock (&data->mutex->fork_mutex[id]);
	}
	data->forks[id] = id;
}

int	put_forks(t_data *data, int id, int left_id)
{
	int	denom;

	denom = (data->num_of_philos & 1) + 2;
	data->forks[id] = -1;
	data->forks[left_id] = -1;
	if (id % denom == 0 || id % denom == 2)
	{
		pthread_mutex_unlock (&data->mutex->fork_mutex[left_id]);
		pthread_mutex_unlock (&data->mutex->fork_mutex[id]);
	}
	else
	{
		pthread_mutex_unlock (&data->mutex->fork_mutex[id]);
		pthread_mutex_unlock (&data->mutex->fork_mutex[left_id]);
	}
	return (1);
}

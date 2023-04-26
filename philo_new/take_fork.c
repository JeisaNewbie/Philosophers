/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:43 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/25 15:58:25 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_data *philos, t_philo *philo, int id, int left_id)
{
	take_forks (philos, philo, id, left_id);
	if (print_status (philos, philo, id, -1))
	{
		philos->forks[id] = -1;
		put_forks (philos, id, left_id);
		return (1);
	}
	if (id == left_id)
	{
		philos->flag = id;
		put_forks (philos, id, left_id);
		return (1);
	}
	philos->forks[left_id] = id;
	philo->usec_before = get_gtd (philo);
	if (print_status (philos, philo, id, -1))
		return (1);
	return (check_died (philos, philo, id, 0));
}

void	take_forks(t_data *philos, t_philo *philo, int id, int left_id)
{
	int	denom;

	denom = philos->num_of_philos % 2 + 2;
	if (id % denom == 0 || id % denom == 2)
	{
		pthread_mutex_lock (&philos->mutex->fork_mutex[id]);
		pthread_mutex_lock (&philos->mutex->fork_mutex[left_id]);
	}
	else
	{
		pthread_mutex_lock (&philos->mutex->fork_mutex[left_id]);
		pthread_mutex_lock (&philos->mutex->fork_mutex[id]);
	}
	philos->forks[id] = id;
	philo->usec_before = get_gtd (philo);
}

void	put_forks(t_data *philos, int id, int left_id)
{
	philos->forks[id] = -1;
	philos->forks[left_id] = -1;
	if (id % 2 == 0)
	{
		pthread_mutex_unlock (&philos->mutex->fork_mutex[left_id]);
		pthread_mutex_unlock (&philos->mutex->fork_mutex[id]);
	}
	else
	{
		pthread_mutex_unlock (&philos->mutex->fork_mutex[id]);
		pthread_mutex_unlock (&philos->mutex->fork_mutex[left_id]);
	}
}

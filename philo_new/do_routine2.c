/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:24:51 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/25 15:55:12 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_all(t_data *philos)
{
	pthread_mutex_lock (&philos->mutex->setting_mutex);
	philos->num_of_philos_eaten++;
	pthread_mutex_unlock (&philos->mutex->setting_mutex);
	return (1);
}

int	p_usleep(t_data *philos, t_philo *philo, int id, u_int64_t time)
{
	u_int64_t	origin;

	origin = philo->usec_before;
	while (1)
	{
		philo->time_to_die += get_gtd (philo)
			- philo->usec_before;
		philo->usec_before = get_gtd (philo);
		if (philo->time_to_die_origin
			< philo->time_to_die)
		{
			pthread_mutex_lock (&philos->mutex->setting_mutex);
			if (philos->flag < 0)
				philos->flag = id;
			pthread_mutex_unlock (&philos->mutex->setting_mutex);
			return (1);
		}
		if (time <= (philo->usec_before - origin))
			return (0);
		usleep (100);
	}
}

int	check_died(t_data *philos, t_philo *philo, int id, int recover)
{
	philo->time_to_die += get_gtd (philo)
		- philo->usec_before;
	philo->usec_before = get_gtd (philo);
	pthread_mutex_lock (&philos->mutex->setting_mutex);
	if (philo->time_to_die_origin < philo->time_to_die
		|| philos->flag >= 0)
	{
		if (philos->flag < 0)
			philos->flag = id;
		pthread_mutex_unlock (&philos->mutex->setting_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock (&philos->mutex->setting_mutex);
		if (recover)
			philo->time_to_die = 0;
		return (0);
	}
}

u_int64_t	get_gtd(t_philo *philo)
{
	gettimeofday (&(philo->tv), NULL);
	return (philo->tv.tv_sec * 1000
		+ philo->tv.tv_usec / 1000);
}

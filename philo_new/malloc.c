/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:23:05 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/25 15:06:37 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_all(t_data *philos)
{
	if (!malloc_mutex (philos))
		return (0);
	if (!malloc_forks (philos))
		return (0);
	return (1);
}

int	malloc_mutex(t_data *philos)
{
	philos->mutex = (t_mutex *)p_calloc (1, sizeof (t_mutex));
	if (philos->mutex == NULL)
		return (0);
	if (pthread_mutex_init (&philos->mutex->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init (&philos->mutex->setting_mutex, NULL) != 0)
	{
		pthread_mutex_destroy (&philos->mutex->print_mutex);
		return (0);
	}
	if (malloc_fork_mutex (philos))
	{
		pthread_mutex_destroy (&philos->mutex->print_mutex);
		pthread_mutex_destroy (&philos->mutex->setting_mutex);
		return (0);
	}
	return (1);
}

int	malloc_fork_mutex(t_data *philos)
{
	int	i;

	i = 0;
	philos->mutex->fork_mutex = (pthread_mutex_t *)p_calloc
		(philos->num_of_philos, sizeof (pthread_mutex_t));
	if (philos->mutex->fork_mutex == NULL)
		return (1);
	while (i < philos->num_of_philos)
	{
		if (pthread_mutex_init (&philos->mutex->fork_mutex[i++], NULL) != 0)
		{
			while (i)
				pthread_mutex_destroy (&philos->mutex->fork_mutex[--i]);
			return (1);
		}
	}
	return (0);
}

int	malloc_forks(t_data *philos)
{
	int	i;

	i = 0;
	philos->forks = (int *)p_calloc (philos->num_of_philos, sizeof (int));
	if (philos->forks == NULL)
	{
		rm_mutex_all (philos, philos->num_of_philos);
		return (0);
	}
	while (i < philos->num_of_philos)
		philos->forks[i++] = -1;
	return (1);
}

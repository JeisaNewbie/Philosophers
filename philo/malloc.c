/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:23:05 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/02 09:27:04 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**malloc_all(t_data *data)
{
	t_philo	**philos;

	if (!malloc_mutex (data))
	{
		if (data->mutex != NULL)
			free (data->mutex);
		return (0);
	}
	if (!malloc_forks (data))
		return (0);
	philos = malloc_philo (data);
	if (philos == NULL)
		return (0);
	return (philos);
}

int	malloc_mutex(t_data *data)
{
	data->mutex = (t_mutex *)p_calloc (1, sizeof (t_mutex));
	if (data->mutex == NULL)
		return (0);
	if (pthread_mutex_init (&data->mutex->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init (&data->mutex->setting_mutex, NULL) != 0)
	{
		pthread_mutex_destroy (&data->mutex->print_mutex);
		return (0);
	}
	if (pthread_mutex_init (&data->mutex->end_mutex, NULL) != 0)
	{
		pthread_mutex_destroy (&data->mutex->print_mutex);
		pthread_mutex_destroy (&data->mutex->setting_mutex);
	}
	if (malloc_fork_mutex (data))
	{
		pthread_mutex_destroy (&data->mutex->print_mutex);
		pthread_mutex_destroy (&data->mutex->setting_mutex);
		pthread_mutex_destroy (&data->mutex->end_mutex);
		return (0);
	}
	return (1);
}

int	malloc_fork_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->mutex->fork_mutex = (pthread_mutex_t *)p_calloc
		(data->num_of_philos, sizeof (pthread_mutex_t));
	if (data->mutex->fork_mutex == NULL)
		return (1);
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init (&data->mutex->fork_mutex[i++], NULL) != 0)
		{
			while (i)
				pthread_mutex_destroy (&data->mutex->fork_mutex[--i]);
			return (1);
		}
	}
	return (0);
}

int	malloc_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = (int *)p_calloc (data->num_of_philos, sizeof (int));
	if (data->forks == NULL)
	{
		rm_mutex_all (data, data->num_of_philos);
		return (0);
	}
	while (i < data->num_of_philos)
		data->forks[i++] = -1;
	return (1);
}

t_philo	**malloc_philo(t_data *data)
{
	t_philo	**philos;
	int		i;

	i = -1;
	philos = (t_philo **)p_calloc
		(data->num_of_philos, sizeof (t_philo *));
	if (philos == NULL)
	{
		rm_mutex_all (data, data->num_of_philos);
		return (0);
	}
	while (++i < data->num_of_philos)
	{
		philos[i] = (t_philo *)p_calloc (1, sizeof (t_philo));
		if (philos[i] == NULL)
		{
			while (--i >= 0)
				free (philos[i]);
			free (philos);
			rm_mutex_all (data, data->num_of_philos);
			return (0);
		}
		init_philo (philos[i], data, i);
	}
	return (philos);
}

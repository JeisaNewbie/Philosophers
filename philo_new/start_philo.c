/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:38:08 by ahkiler           #+#    #+#             */
/*   Updated: 2023/04/27 16:58:57 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philo(t_data *philos)
{
	int	i;

	i = 0;
	while (i < (philos->num_of_philos & 1) + 2)
	{
		create_pth (philos, i++);
		usleep (100);
	}
}

void	create_pth(t_data *philos, int i)
{
	pthread_t	philo;

	philos->id = i;
	while (i < philos->num_of_philos)
	{
		pthread_create (&philo, 0, start_pth, (void *)philos);
		pthread_detach (philo);
		usleep (10);
		pthread_mutex_lock (&philos->mutex->setting_mutex);
		philos->id += (philos->num_of_philos % 2) + 2;
		i += (philos->num_of_philos % 2) + 2;
		pthread_mutex_unlock (&philos->mutex->setting_mutex);
	}
}

void	*start_pth(void *arg)
{
	t_data	*philos;
	t_philo	philo;
	int		left_id;
	int		id;

	philos = (t_data *)arg;
	pthread_mutex_lock (&philos->mutex->setting_mutex);
	id = philos->id;
	if (id == 0)
		init_time (philos, &philo);
	pthread_mutex_unlock (&philos->mutex->setting_mutex);
	init_philo (philos, &philo, &id, &left_id);
	do_routine (philos, &philo, id, left_id);
	end_pth (philos);
	return (0);
}

void	end_pth(t_data *philos)
{
	pthread_mutex_lock (&philos->mutex->setting_mutex);
	philos->end++;
	pthread_mutex_unlock (&philos->mutex->setting_mutex);
}

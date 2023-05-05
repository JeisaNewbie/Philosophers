/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine_utiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:24:51 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/05 11:00:30 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_all(t_data *data, int id)
{
	pthread_mutex_lock (&data->mutex->setting_mutex);
	data->num_of_philos_eaten++;
	if (data->num_of_philos_eaten == data->num_of_philos * 2)
	{
		data->end = id + 1;
		pthread_mutex_unlock (&data->mutex->setting_mutex);
		return (1);
	}
	pthread_mutex_unlock (&data->mutex->setting_mutex);
	return (0);
}

int	sleeping(t_data *data, t_philo *philo, int id)
{
	if (!end_pth (data))
		return (1);
	print_status (data, philo, id, "is sleeping");
	return (p_usleep (data, philo, id, philo->time_to_sleep));
}

int	p_usleep(t_data *data, t_philo *philo, int id, u_int64_t time)
{
	u_int64_t	origin;

	origin = philo->usec_before;
	while (end_pth (data))
	{
		philo->time_to_die += get_gtd ()
			- philo->usec_before;
		philo->usec_before = get_gtd ();
		if (philo->time_to_die_origin
			<= philo->time_to_die)
		{
			pthread_mutex_lock (&data->mutex->setting_mutex);
			if (data->end == 0)
				data->end = id + 1;
			pthread_mutex_unlock (&data->mutex->setting_mutex);
			return (1);
		}
		if (time <= (philo->usec_before - origin))
			return (0);
		usleep (100);
	}
	return (1);
}

u_int64_t	get_gtd(void)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return (tv.tv_sec * 1000
		+ tv.tv_usec / 1000);
}

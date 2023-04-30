/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:24:51 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/30 04:13:37 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_usleep(t_data *data, t_philo *philo, u_int64_t time)
{
	u_int64_t	origin;

	origin = philo->usec_before;
	while (1)
	{
		philo->time_to_die += get_gtd () - philo->usec_before;
		philo->usec_before = get_gtd ();
		if (philo->time_to_die_origin <= philo->time_to_die)
		{
			sem_wait (data->sem->sem_print);
			printf ("%llums\t%d\tis died\n", philo->usec_before
				- data->time_to_start, philo->id);
			close_sem (data, 7);
			exit (0);
		}
		if (time <= (philo->usec_before - origin))
			return (0);
		usleep (100);
	}
	return (0);
}

u_int64_t	get_gtd(void)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

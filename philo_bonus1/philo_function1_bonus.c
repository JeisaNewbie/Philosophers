/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:14:36 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/05 14:23:11 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_data *philos, t_philo *philo, int id, char *str)
{
	sem_wait (philos->sem->sem_print);
	if (philo->time_to_die_origin <= get_gtd () - philo->usec_before)
	{
		close_sem (philos, 4);
		exit (0);
	}
	printf ("%llu %d %s\n", get_gtd () - philos->time_to_start, id + 1, str);
	sem_post (philos->sem->sem_print);
	philo->usec_before = get_gtd ();
	return ;
}

void	p_usleep(t_data *philos, t_philo *philo, u_int64_t time)
{
	u_int64_t	origin;

	origin = philos->philo->usec_before;
	while (1)
	{
		philo->time_to_die += get_gtd () - philo->usec_before;
		philo->usec_before = get_gtd ();
		if (philo->time_to_die_origin <= philo->time_to_die)
		{
			sem_wait (philos->sem->sem_print);
			printf ("%llu %d died\n", get_gtd ()
				- philos->time_to_start, philos->id + 1);
			close_sem (philos, 4);
			exit (1);
		}
		if (time <= (philo->usec_before - origin))
			return ;
		usleep (100);
	}
}

u_int64_t	get_gtd(void)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

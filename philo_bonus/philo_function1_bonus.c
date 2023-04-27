/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:14:36 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/27 15:03:45 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_data *philos, t_philo *philo, int id, int flag)
{
	u_int64_t	time;

	is_died(philos, philo);
	philo->usec_before = get_gtd ();
	time = philo->usec_before - philos->time_to_start;
	sem_wait (philos->sem_print);
	if (flag == 1)
	{
		printf ("%llums\t%d\thas taken a fork\t%d\n", time, id, philo->eaten);
		printf ("%llums\t%d\thas taken a fork\t%d\n", time, id, philo->eaten);
	}
	else if (flag == 2)
		printf ("%llums\t%d\tis eating\t\t%d\n", time, id, philo->eaten);
	else if (flag == 3)
		printf ("%llums\t%d\tis sleeping\t\t%d\n", time, id, philo->eaten);
	else if (flag == 4)
		printf ("%llums\t%d\tis thinking\t\t%d\n", time, id, philo->eaten);
	else if (flag == 5)
		printf ("all philosophers have eaten all\n");
	sem_post (philos->sem_print);
	return ;
}

void	close_sem(t_data *philos)
{
	sem_close (philos->forks);
	sem_close (philos->sem_print);
	sem_close (philos->philo->wait);
}

void	p_usleep(t_data *philos, int flag)
{
	u_int64_t	time;
	u_int64_t	origin;

	origin = philos->philo->usec_before;
	if (flag == -2)
		time = philos->philo->time_to_eat;
	else
		time = philos->philo->time_to_sleep;
	while (1)
	{
		is_died (philos, philos->philo);
		if (time <= (get_gtd () - origin))
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

void	is_died(t_data *philos, t_philo *philo)
{
	philo->time_to_die += get_gtd () - philo->usec_before;
	philo->usec_before = get_gtd ();
	if (philo->time_to_die_origin <= philo->time_to_die)
	{
		sem_wait (philos->sem_print);
		printf ("%llums\t%d\tis died\n", philo->usec_before
			- philos->time_to_start, philos->id);
		close_sem (philos);
		exit (1);
	}
}

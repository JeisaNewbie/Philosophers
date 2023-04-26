/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:48 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/25 15:56:27 by ahkiler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_routine(t_data *philos, t_philo *philo, int id, int left_id)
{
	int	start;

	start = 1;
	while (1)
	{
		if (take_fork(philos, philo, id, left_id))
			return ;
		if (start)
		{
			philo->time_to_die += philo->usec_before - philos->time_to_start;
			start = 0;
		}
		if (eating (philos, philo, id, left_id))
			return ;
		if (sleeping (philos, philo, id))
			return ;
		if (thinking (philos, philo, id))
			return ;
	}
}

int	eating(t_data *philos, t_philo *philo, int id, int left_id)
{
	philo->usec_before = get_gtd (philo);
	if (print_status (philos, philo, id, -2))
		return (1);
	if (p_usleep (philos, philo, id, philo->time_to_eat))
	{
		put_forks (philos, id, left_id);
		return (1);
	}
	philo->eaten++;
	put_forks (philos, id, left_id);
	if (philo->num_of_time_to_eat != -1)
	{
		philo->num_of_time_to_eat--;
		if (philo->num_of_time_to_eat == 0)
			return (eating_all (philos));
	}
	return (check_died (philos, philo, id, 1));
}

int	sleeping(t_data *philos, t_philo *philo, int id)
{
	philo->usec_before = get_gtd (philo);
	if (print_status (philos, philo, id, -3))
		return (1);
	return (p_usleep (philos, philo, id, philo->time_to_sleep));
}

int	thinking(t_data *philos, t_philo *philo, int id)
{
	philo->usec_before = get_gtd (philo);
	if (print_status (philos, philo, id, -4))
		return (1);
	return (check_died (philos, philo, id, 0));
}

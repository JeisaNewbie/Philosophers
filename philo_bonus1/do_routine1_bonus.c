/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:14:22 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/05 14:56:42 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine_odd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:14:22 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/05 14:07:40 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	do_routine_odd(t_data *philos)
{
	if (philos->num_of_philos == 1)
	{
		sem_wait (philos->sem->forks);
		print_status (philos, philos->philo, 0, "has taken a fork");
		p_usleep (philos, philos->philo, philos->philo->time_to_die_origin * 2);
	}
	if (philos->id == philos->num_of_philos - 1)
		p_usleep (philos, philos->philo, philos->philo->time_to_eat * 2);
	while (1)
	{
		take_fork(philos);
		if (eating (philos))
			return ;
		put_fork (philos);
		sleeping (philos);
		thinking_odd (philos);
	}
}

int	thinking_odd(t_data *philos)
{
	print_status (philos, philos->philo, philos->id, "is thinking");
	if (philos->philo->time_to_eat * 2 > philos->philo->time_to_sleep)
		p_usleep (philos, philos->philo,
			philos->philo->time_to_eat * 2 - philos->philo->time_to_sleep);
	return (0);
}

void	do_routine(t_data *philos)
{
	while (1)
	{
		take_fork(philos);
		if (eating (philos))
			return ;
		put_fork (philos);
		sleeping (philos);
		thinking (philos);
	}
}

int	eating(t_data *philos)
{
	philos->philo->time_to_die = 0;
	if (philos->philo->num_of_time_to_eat != -1)
	{
		philos->philo->num_of_time_to_eat--;
		if (philos->philo->num_of_time_to_eat == 0)
			sem_post (philos->sem->sem_eaten);
	}
	print_status (philos, philos->philo, philos->id, "is eating");
	p_usleep (philos, philos->philo, philos->philo->time_to_eat);
	return (0);
}

int	sleeping(t_data *philos)
{
	print_status (philos, philos->philo, philos->id, "is sleeping");
	p_usleep (philos, philos->philo, philos->philo->time_to_sleep);
	return (0);
}

int	thinking(t_data *philos)
{
	print_status (philos, philos->philo, philos->id, "is thinking");
	if (philos->philo->time_to_eat > philos->philo->time_to_sleep)
		p_usleep (philos, philos->philo,
			philos->philo->time_to_eat - philos->philo->time_to_sleep);
	return (0);
}

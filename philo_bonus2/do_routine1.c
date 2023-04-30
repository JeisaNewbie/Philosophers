/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:48 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/30 04:20:07 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_routine(t_data *data, t_philo *philo)
{
	while (1)
	{
		take_fork(data, philo);
		eating (data, philo);
		put_fork (data);
		sleeping (data, philo);
		thinking (data, philo);
	}
}

void	eating(t_data *data, t_philo *philo)
{
	print_status (data, philo, philo->id, "is eating");
	p_usleep (data, philo, philo->time_to_eat);
	philo->time_to_die = 0;
	philo->eaten++;
	if (philo->num_of_time_to_eat != -1)
	{
		if (philo->eaten >= philo->num_of_time_to_eat)
			eating_all (data);
	}
}

void	eating_all(t_data *data)
{
	sem_wait (data->sem->sem_setting);
	data->num_of_philos_eaten++;
	if (data->num_of_philos_eaten == data->num_of_philos)
	{
		sem_wait (data->sem->sem_print);
		printf ("all philosophers have eaten all\n");
		exit (0);
	}
	sem_post (data->sem->sem_setting);
}

void	sleeping(t_data *data, t_philo *philo)
{
	print_status (data, philo, philo->id, "is sleeping");
	p_usleep (data, philo, philo->time_to_sleep);
}

void	thinking(t_data *data, t_philo *philo)
{
	print_status (data, philo, philo->id, "is thinking");
}

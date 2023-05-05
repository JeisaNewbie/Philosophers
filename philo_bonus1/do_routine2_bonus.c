/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:14:27 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/01 15:41:45 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(t_data *philos)
{
	sem_wait (philos->sem->forks);
	sem_wait (philos->sem->forks);
	print_status (philos, philos->philo, philos->id, "has taken a fork");
	print_status (philos, philos->philo, philos->id, "has taken a fork");
	if (philos->philo->time_to_die == 0)
		philos->philo->time_to_die += get_gtd () - philos->time_to_start;
}

void	put_fork(t_data *philos)
{
	sem_post (philos->sem->forks);
	sem_post (philos->sem->forks);
}

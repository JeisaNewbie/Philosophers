/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:43 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/30 04:17:37 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_data *data, t_philo *philo)
{
	sem_wait (data->sem->forks);
	sem_wait (data->sem->forks);
	print_status (data, philo, philo->id, "has taken a fork");
	print_status (data, philo, philo->id, "has taken a fork");
}

void	put_fork(t_data *data)
{
	sem_post (data->sem->forks);
	sem_post (data->sem->forks);
}

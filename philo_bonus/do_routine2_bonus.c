/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:14:27 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/27 15:05:21 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(t_data *philos)
{
	sem_wait (philos->forks);
	sem_wait (philos->forks);
	print_status (philos, philos->philo, philos->id, 1);
}

void	put_fork(t_data *philos)
{
	sem_post (philos->forks);
	sem_post (philos->forks);
}

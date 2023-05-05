/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 01:52:51 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/01 15:57:09 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	close_sem(t_data *philos, int i)
{
	if (i == 2)
		sem_close (philos->sem->forks);
	else if (i == 3)
	{
		sem_close (philos->sem->forks);
		sem_close (philos->sem->sem_print);
	}
	else if (i == 4)
	{
		sem_close (philos->sem->forks);
		sem_close (philos->sem->sem_print);
		sem_close (philos->sem->sem_eaten);
	}
	return (1);
}

// void	close_sem_all(t_data *data, int i)
// {
// 	if (i == 6)
// 	{
// 		sem_close (data->sem->forks);
// 		sem_close (data->sem->sem_print);
// 		sem_close (data->sem->sem_setting);
// 		sem_close (data->sem->start[0]);
// 		sem_close (data->sem->start[1]);
// 	}
// 	else
// 	{
// 		sem_close (data->sem->forks);
// 		sem_close (data->sem->sem_print);
// 		sem_close (data->sem->sem_setting);
// 		sem_close (data->sem->start[0]);
// 		sem_close (data->sem->start[1]);
// 		sem_close (data->sem->start[2]);
// 	}
// }

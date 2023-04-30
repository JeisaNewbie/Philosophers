/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 01:52:51 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/30 03:48:33 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	close_sem(t_data *data, int i)
{
	if (i == 2)
		sem_close (data->sem->forks);
	else if (i == 3)
	{
		sem_close (data->sem->forks);
		sem_close (data->sem->sem_print);
	}
	else if (i == 4)
	{
		sem_close (data->sem->forks);
		sem_close (data->sem->sem_print);
		sem_close (data->sem->sem_setting);
	}
	else if (i == 5)
	{
		sem_close (data->sem->forks);
		sem_close (data->sem->sem_print);
		sem_close (data->sem->sem_setting);
		sem_close (data->sem->s_one);
	}
	else if (i == 6 || i == 7)
		close_sem_all (data, i);
	free (data->philos);
	return (1);
}

void	close_sem_all(t_data *data, int i)
{
	if (i == 6)
	{
		sem_close (data->sem->forks);
		sem_close (data->sem->sem_print);
		sem_close (data->sem->sem_setting);
		sem_close (data->sem->s_one);
		sem_close (data->sem->s_two);
	}
	else
	{
		sem_close (data->sem->forks);
		sem_close (data->sem->sem_print);
		sem_close (data->sem->sem_setting);
		sem_close (data->sem->s_one);
		sem_close (data->sem->s_two);
		sem_close (data->sem->s_three);
	}
}

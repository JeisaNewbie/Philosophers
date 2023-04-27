/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:14:07 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/27 14:17:24 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	fork_proc(t_data *philos)
{
	if (fork_child (philos))
		return (1);
	if (philos->pid > 0)
		wait_and_kill (philos);
	else
		start (philos);
	return (0);
}

int	fork_child(t_data *philos)
{
	int		i;

	i = 0;
	init_time (philos);
	while (i < (philos->num_of_philos % 2) + 2)
	{
		if (start_philo (philos, i++))
			return (1);
		if (philos->pid == 0)
			return (0);
		usleep (100);
	}
	return (0);
}

int	start_philo(t_data *philos, int i)
{
	while (i < philos->num_of_philos)
	{
		philos->pid = fork ();
		if (philos->pid < 0)
			return (kill_proc (philos));// 자식프로세스 kill하기 전에 sem_wait으로 모든 자식프로세스가 sem_close했는지 대기 필요
		if (philos->pid == 0)
		{
			philos->id = i;
			return (0);
		}
		philos->philos[i] = philos->pid;
		i += (philos->num_of_philos % 2) + 2;
	}
	return (0);
}

int	start(t_data *philos)
{
	t_philo		philo;

	philos->philo = &philo;
	init_philo (philos, philos->philo, philos->argv);
	do_routine (philos);
	return (0);
}

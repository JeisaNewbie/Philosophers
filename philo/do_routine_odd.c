/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_routine_odd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:48 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/04 18:13:59 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_routine_odd(t_philo *philo, t_data *data, int id, int left_id)
{
	if (id == left_id)
	{
		data->forks[id] = id;
		print_status (data, philo, id, "has taken a fork");
		p_usleep (data, philo, id, philo->time_to_die_origin * 2);
		return ;
	}
	while (1)
	{
		if (take_fork_odd(data, philo, id, left_id))
			return ;
		if (eating_odd (data, philo, id, left_id))
			return ;
		if (sleeping (data, philo, id))
			return ;
		if (thinking (data, philo, id))
			return ;
	}
}

int	eating_odd(t_data *data, t_philo *philo, int id, int left_id)
{
	if (philo->num_of_time_to_eat != -1)
	{
		if (++philo->eaten == philo->num_of_time_to_eat)
		{
			if (eating_all (data, id))
			{
				put_forks_odd (data, id, left_id);
				return (1);
			}
		}
	}
	philo->time_to_die = 0;
	if (!end_pth (data))
		return (put_forks (data, id, left_id));
	print_status (data, philo, id, "is eating");
	if (p_usleep (data, philo, id, philo->time_to_eat))
	{
		put_forks_odd (data, id, left_id);
		return (1);
	}
	put_forks_odd (data, id, left_id);
	return (0);
}

int	thinking_odd(t_data *data, t_philo *philo, int id)
{
	if (!end_pth (data))
		return (1);
	print_status (data, philo, id, "is thinking");
	return (p_usleep (data, philo, id,
			philo->time_to_eat - philo->time_to_sleep + philo->time_to_eat));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:34 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/27 17:18:11 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//시간 엉키는거
//밥 다먹어도 행동
//데이터 레이스
//end_flag 수시체크
int	main(int argc, char *argv[])
{
	t_data		philos;

	if (check_vaild (argc, argv))
		return (1);
	if (!init_philos (&philos, argv))
		return (1);
	start_philo (&philos);
	monitoring_pthread (&philos);
	return (0);
}

int	wait_pth(t_data *philos, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock (&philos->mutex->setting_mutex);
		if (philos->flag >= 0)
		{
			philo->usec_before = get_gtd (philo);
			pthread_mutex_unlock (&philos->mutex->setting_mutex);
			return (1);
		}
		if (philos->num_of_philos_eaten == philos->num_of_philos * 2)
		{
			pthread_mutex_unlock (&philos->mutex->setting_mutex);
			return (0);
		}
		pthread_mutex_unlock (&philos->mutex->setting_mutex);
	}
}

void	monitoring_pthread(t_data *philos)
{
	t_philo	philo;
	int		error;

	init_philo (philos, &philo, 0, 0);
	error = wait_pth (philos, &philo);
	if (error == 1)
	{
		while (philos->end != philos->num_of_philos)
			;
		print_status (philos, &philo, 0, philos->flag);
	}
	else
		printf ("all philosophers have eaten all\n");
	rm_mutex_all (philos, philos->num_of_philos);
	return ;
}

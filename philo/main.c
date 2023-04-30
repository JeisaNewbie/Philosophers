/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:34 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/29 20:27:14 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo		**philos;
	t_data		data;

	if (check_vaild (argc, argv))
		return (1);
	philos = init_philos (&data, argv);
	if (philos == NULL)
		return (1);
	start_philo (philos, &data);
	monitoring_pthread (&data);
	return (0);
}

void	start_philo(t_philo **philos, t_data *data)
{
	int			i;

	i = 0;
	while (i < (data->num_of_philos & 1) + 2)
	{
		create_pth (philos, data, i++);
		usleep (100);
	}
}

void	monitoring_pthread(t_data *data)
{
	int		error;

	error = 1;
	wait_pth (data, &error);
	if (error)
		printf ("%llu %d %s\n",
			get_gtd () - data->time_to_start, error, "is died");
	else
		printf ("all philosophers have eaten all\n");
	rm_mutex_all (data, data->num_of_philos);
	return ;
}

void	wait_pth(t_data *data, int *error)
{
	int		i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock (&data->mutex->end_mutex);
		if (data->num_of_philos_ended == data->num_of_philos)
			break ;
		pthread_mutex_unlock (&data->mutex->end_mutex);
	}
	pthread_mutex_unlock (&data->mutex->end_mutex);
	pthread_mutex_lock (&data->mutex->setting_mutex);
	if (data->num_of_philos_eaten == data->num_of_philos * 2)
			*error = 0;
	else
		*error = data->end;
	pthread_mutex_unlock (&data->mutex->setting_mutex);
}

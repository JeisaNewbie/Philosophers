/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:40 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/29 20:07:29 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philos(t_data *data, char **argv)
{
	init_base (data, argv);
	return (malloc_all (data));
}

void	init_base(t_data *data, char **argv)
{
	data->num_of_philos = p_atoi (argv[1]);
	data->end = 0;
	data->argv = argv;
	data->num_of_philos_ended = 0;
	if (argv[5] != NULL)
		data->num_of_philos_eaten = data->num_of_philos;
	else
		data->num_of_philos_eaten = -1;
}

void	init_philo(t_philo *philos, t_data *data, int id)
{
	philos->id = id;
	philos->data = data;
	if (id == 0)
		philos->left_id = data->num_of_philos - 1;
	else if (id != 0)
		philos->left_id = id - 1;
	philos->time_to_die = 0;
	philos->time_to_die_origin = (u_int64_t)p_atoi (data->argv[2]);
	philos->time_to_eat = (u_int64_t)p_atoi (data->argv[3]);
	philos->time_to_sleep = (u_int64_t)p_atoi (data->argv[4]);
	philos->eaten = 0;
	if (data->argv[5] != NULL)
		philos->num_of_time_to_eat = p_atoi (data->argv[5]);
	else
		philos->num_of_time_to_eat = -1;
}

void	init_time(t_data *data)
{
	data->time_to_start = get_gtd ();
}

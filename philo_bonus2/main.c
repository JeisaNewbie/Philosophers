/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:34 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/30 04:19:13 by jhwang2          ###   ########.fr       */
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
	return (0);
}

void	start_philo(t_philo **philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->num_of_philos & 1) + 2)
		create_pth (philos, data, i++);
	while (i < (data->num_of_philos & 1) + 2)
		start_proc (data, i++);
	wait_proc (data);
}

void	start_proc(t_data *data, int i)
{
	if (i == 0)
		init_time (data);
	while (i < data->num_of_philos)
	{
		if (i % (data->num_of_philos & 1) + 2 == 0)
			sem_post (data->sem->s_one);
		else if (i % (data->num_of_philos & 1) + 2 == 1)
			sem_post (data->sem->s_two);
		else if (i % (data->num_of_philos & 1) + 2 == 2)
			sem_post (data->sem->s_three);
		i += (data->num_of_philos & 1) + 2;
	}
}

void	wait_proc(t_data *data)
{
	int	status;
	int	ret;
	int	i;

	status = 0;
	i = -1;
	ret = waitpid (-1, &status, 0);
	while (++i < data->num_of_philos)
	{
		if (ret == data->philos[i])
		{
			data->philos[i] = -1;
			kill_proc (data);
			return ;
		}
	}
}

void	kill_proc(t_data *data)
{
	int			i;
	int			philo_died;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philos[i] == -1)
		{
			philo_died = i++;
			continue ;
		}
		kill (data->philos[i++], SIGKILL);
	}
	return ;
}

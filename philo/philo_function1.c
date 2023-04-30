/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:52 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/29 19:42:21 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_vaild(int argc, char **argv)
{
	int	i[2];

	i[0] = 0;
	i[1] = -1;
	if (!(5 <= argc && argc <= 6))
	{
		printf ("not enough option!!!\n");
		return (1);
	}
	while (argv[++i[0]])
	{
		while (argv[i[0]][++i[1]])
		{
			if (!('0' <= argv[i[0]][i[1]] && argv[i[0]][i[1]] <= '9'))
			{
				printf ("option is not an integer!!!\n");
				return (1);
			}
		}
		i[1] = -1;
	}
	return (check_argument (argv));
}

int	check_argument(char **argv)
{
	int	error;

	error = 0;
	if (argv[1][0] == '0' && argv[1][1] == '\0')
		error = 1;
	else if (argv[2][0] == '0' && argv[2][1] == '\0')
		error = 1;
	else if (argv[5] != 0 && argv[5][0] == '0' && argv[5][1] == '\0')
		error = 2;
	else
		return (0);
	if (error == 1)
		printf ("not valid argument!!!\n");
	else
		printf ("all philosophers have eaten all\n");
	return (1);
}

void	print_status(t_data *data, t_philo *philo, int id, char *str)
{
	pthread_mutex_lock (&data->mutex->print_mutex);
	printf ("%llu %d %s\n", get_gtd () - data->time_to_start, id + 1, str);
	pthread_mutex_unlock (&data->mutex->print_mutex);
	philo->usec_before = get_gtd ();
}

void	rm_mutex_all(t_data *data, int end)
{
	int	i;

	i = 0;
	while (i < end)
		pthread_mutex_destroy (&data->mutex->fork_mutex[i++]);
	i = 0;
	pthread_mutex_destroy (&data->mutex->print_mutex);
	pthread_mutex_destroy (&data->mutex->setting_mutex);
	pthread_mutex_destroy (&data->mutex->end_mutex);
	free (data->mutex->fork_mutex);
	free (data->mutex);
	if (data->forks)
		free (data->forks);
}

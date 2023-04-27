/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:52 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/27 17:09:17 by jhwang2          ###   ########.fr       */
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

int	print_status(t_data *philos, t_philo *philo, int id, int flag)
{
	u_int64_t	time;

	time = philo->usec_before - philos->time_to_start;
	pthread_mutex_lock (&philos->mutex->print_mutex);
	pthread_mutex_lock (&philos->mutex->setting_mutex);
	if (philos->flag >= 0 && flag < 0)
	{
		pthread_mutex_unlock (&philos->mutex->setting_mutex);
		pthread_mutex_unlock (&philos->mutex->print_mutex);
		return (1);
	}
	pthread_mutex_unlock (&philos->mutex->setting_mutex);
	if (flag == -1)
		printf ("%llu %d has taken a fork\n", time, id);
	else if (flag == -2)
		printf ("%llu %d is eating\n", time, id);
	else if (flag == -3)
		printf ("%llu %d is sleeping\n", time, id);
	else if (flag == -4)
		printf ("%llu %d is thinking\n", time, id);
	else
		printf ("%llu %d is died\n", time, flag);
	pthread_mutex_unlock (&philos->mutex->print_mutex);
	return (0);
}

void	rm_mutex_all(t_data *philos, int end)
{
	int	i;

	i = 0;
	while (i < end)
		pthread_mutex_destroy (&philos->mutex->fork_mutex[i++]);
	i = 0;
	pthread_mutex_destroy (&philos->mutex->print_mutex);
	pthread_mutex_destroy (&philos->mutex->setting_mutex);
	free (philos->mutex->fork_mutex);
	if (philos->forks)
		free (philos->forks);
}

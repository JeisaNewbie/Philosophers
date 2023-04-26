/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkiler <ahkiler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:01:52 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/25 16:15:53 by ahkiler          ###   ########.fr       */
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
		printf ("%llums\t%d\thas taken a fork\t%d\n", time, id, philo->eaten);
	else if (flag == -2)
		printf ("%llums\t%d\tis eating\t\t%d\n", time, id, philo->eaten);
	else if (flag == -3)
		printf ("%llums\t%d\tis sleeping\t\t%d\n", time, id, philo->eaten);
	else if (flag == -4)
		printf ("%llums\t%d\tis thinking\t\t%d\n", time, id, philo->eaten);
	else
		printf ("%llums\t%d\tis died\n", time, flag);
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

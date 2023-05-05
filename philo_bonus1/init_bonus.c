/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:06:08 by jhwang2           #+#    #+#             */
/*   Updated: 2023/05/01 17:01:47 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philos(t_data *philos, char **argv)
{
	if (!init_base (philos, argv))
		return (0);
	if (creat_sem (philos))
		return (0);
	return (1);
}

int	init_base(t_data *philos, char **argv)
{
	philos->num_of_philos = p_atoi (argv[1]);
	philos->philos = (pid_t *)p_calloc (philos->num_of_philos, sizeof (pid_t));
	if (philos->philos == NULL)
		return (0);
	philos->sem = (t_sem *)p_calloc (1, sizeof (t_sem));
	if (philos->sem == NULL)
	{
		free (philos->philos);
		return (0);
	}
	philos->num_of_proc_ended = 0;
	philos->argv = argv;
	philos->flag = -1;
	philos->id = 0;
	return (1);
}

void	init_philo(t_data *philos, t_philo *philo, char **argv)
{
	philo->eaten = 0;
	philo->time_to_die = 0;
	philo->time_to_die_origin = (u_int64_t)p_atoi (argv[2]);
	philo->time_to_eat = (u_int64_t)p_atoi (argv[3]);
	philo->time_to_sleep = (u_int64_t)p_atoi (argv[4]);
	if (argv[5] != NULL)
		philo->num_of_time_to_eat = p_atoi (argv[5]);
	else
		philo->num_of_time_to_eat = -1;
	philo->usec_before = get_gtd ();
	philos = philos + 0;
}

void	init_time(t_data *philos)
{
	philos->time_to_start = get_gtd ();
}

int	creat_sem(t_data *philos)
{
	philos->sem->forks = sem_open ("forks",
			O_CREAT, 0666, philos->num_of_philos);
	if (philos->sem->forks == SEM_FAILED)
		return (close_sem (philos, 1));
	sem_unlink ("forks");
	philos->sem->sem_print = sem_open ("sem_print", O_CREAT, 0666, 1);
	if (philos->sem->sem_print == SEM_FAILED)
		return (close_sem (philos, 2));
	sem_unlink ("sem_print");
	philos->sem->sem_eaten = sem_open ("sem_eaten", O_CREAT, 0666, 0);
	if (philos->sem->sem_eaten == SEM_FAILED)
		return (close_sem (philos, 3));
	sem_unlink ("sem_eaten");
	return (1);
}

#include "philo_bonus.h"

void	do_routine(t_data *philos)
{
	while (1)
	{
		take_fork(philos);
		if (eating (philos))
			return ;
		put_fork (philos);
		sleeping (philos);
		thinking (philos);
	}
}

int	eating(t_data *philos)
{
	print_status (philos, philos->id, 2);
	p_usleep (philos, -2);
	philos->philo->time_to_die = 0;
	philos->philo->eaten++;
	if (philos->philo->num_of_time_to_eat != -1)
	{
		philos->philo->num_of_time_to_eat--;
		if (philos->philo->num_of_time_to_eat == 0)
			return (eating_all (philos));
	}
	return (0);
}

int	eating_all(t_data *philos)
{
	put_fork (philos);
	close_sem (philos);
	exit (0);
}

int	sleeping(t_data *philos)
{
	print_status (philos, philos->id, 3);
	p_usleep (philos, -3);
	return (0);
}

int	thinking(t_data *philos)
{
	print_status (philos, philos->id, 4);
	return (0);
}

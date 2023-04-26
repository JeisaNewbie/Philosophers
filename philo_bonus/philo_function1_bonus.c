#include "philo_bonus.h"

void	print_status(t_data *philos, int id, int flag)
{
	u_int64_t	time;

	philos->philo->usec_before = get_gtd ();
	time = philos->philo->usec_before - philos->time_to_start;
	sem_wait (philos->sem_print);
	if (flag == 1)
	{
		printf ("%llums\t%d\thas taken a fork\t%d\n", time, id, philos->philo->eaten);
		printf ("%llums\t%d\thas taken a fork\t%d\n", time, id, philos->philo->eaten);
	}
	else if (flag == 2)
		printf ("%llums\t%d\tis eating\t\t%d\n", time, id, philos->philo->eaten);
	else if (flag == 3)
		printf ("%llums\t%d\tis sleeping\t\t%d\n", time, id, philos->philo->eaten);
	else if (flag == 4)
		printf ("%llums\t%d\tis thinking\t\t%d\n", time, id, philos->philo->eaten);
	else if (flag == 5)
		printf ("all philosophers have eaten all\n");
	else
		printf ("%llums\t%d\tis died\t\t\t%d\n", time, id, philos->philo->eaten);
	sem_post (philos->sem_print);
	return ;
}

void	close_sem(t_data *philos)
{
	sem_close (philos->forks);
	sem_close (philos->sem_print);
	sem_close (philos->philo->wait);
}

void	p_usleep(t_data *philos, int flag)
{
	u_int64_t	time;
	u_int64_t	origin;

	origin = philos->philo->usec_before;
	if (flag == -2)
		time = philos->philo->time_to_eat;
	else
		time = philos->philo->time_to_sleep;
	while (1)
	{
		philos->philo->time_to_die += get_gtd () - philos->philo->usec_before;
		philos->philo->usec_before = get_gtd ();
		if (philos->philo->time_to_die_origin <= philos->philo->time_to_die)
		{
			put_fork (philos);
			sem_wait (philos->sem_print);
			close_sem (philos);
			exit (1);
		}
		if (time <= (get_gtd () - origin))
			return ;
		usleep (10);
	}
}

u_int64_t	get_gtd(void)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

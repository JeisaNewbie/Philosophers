#include "philo_bonus.h"

void	take_fork(t_data *philos)
{
	sem_wait (philos->forks);
	sem_wait (philos->forks);
	philos->flag = 1;
	usleep (100);
	sem_wait (philos->philo.wait);
	sem_post (philos->philo.wait);
}

void	put_fork(t_data *philos)
{
	sem_post (philos->forks);
	sem_post (philos->forks);
}
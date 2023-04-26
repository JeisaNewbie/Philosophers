#include "philo_bonus.h"

void	take_fork(t_data *philos)
{
	sem_wait (philos->forks);
	sem_wait (philos->forks);
	print_status (philos, philos->id, 1);
}

void	put_fork(t_data *philos)
{
	sem_post (philos->forks);
	sem_post (philos->forks);
}
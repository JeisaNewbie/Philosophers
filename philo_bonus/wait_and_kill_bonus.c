#include "philo_bonus.h"

void	wait_and_kill(t_data *philos)
{
	t_philo	philo;

	philos->philo = &philo;
	init_philo (philos, philos->philo, philos->argv);
	if (wait_proc (philos))
		kill_proc (philos);
	else
		print_status (philos, philos->id, 5);
	sem_close (philos->forks);
	sem_close (philos->sem_print);
}

int	wait_proc(t_data *philos)
{
	int	status;
	int	ret;
	int	i;

	status = 0;
	while (!WEXITSTATUS(status))
	{
		i = -1;
		ret = waitpid (-1, &status, 0);
		while (++i < philos->num_of_philos)
		{
			if (ret == philos->philos[i])
			{
				philos->philos[i] = -1;
				philos->num_of_proc_ended++;
				break ;
			}
		}
		if (philos->num_of_proc_ended == philos->num_of_philos)
			break ;
	}
	if (WEXITSTATUS(status))
		return (1);
	return (0);
}

int	kill_proc(t_data *philos)
{
	int	i;
	int	philo_died;

	i = 0;
	while (i < philos->num_of_philos)
	{
		if (philos->philos[i] == -1)
		{
			philo_died = i++;
			continue ;
		}
		kill (philos->philos[i++], SIGKILL);
	}
	sem_post (philos->sem_print);
	print_status (philos, philo_died, 6);
	return (1);
}

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	philos;

	if (check_vaild (argc, argv)) //manda ㅎㅏㅁ수로 수수정  필필요요
		return (1);
	init_philos (&philos, argv);
	if (fork_proc(&philos))
	{
		printf ("fork failure!!!\n");
		return (1);
	}
}

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
				printf ("option is not integer!!!\n");
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

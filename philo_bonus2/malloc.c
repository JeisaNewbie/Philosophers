/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:23:05 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/30 01:55:56 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**malloc_all(t_data *data)
{
	t_philo	**philos;

	philos = malloc_philo (data);
	if (philos == NULL)
	{
		close_sem (data, 6);
		return (0);
	}
	return (philos);
}

t_philo	**malloc_philo(t_data *data)
{
	t_philo	**philos;
	int		i;

	i = -1;
	philos = (t_philo **)p_calloc
		(data->num_of_philos, sizeof (t_philo *));
	if (philos == NULL)
		return (0);
	while (++i < data->num_of_philos)
	{
		philos[i] = (t_philo *)p_calloc (1, sizeof (t_philo));
		if (philos[i] == NULL)
		{
			while (--i >= 0)
				free (philos[i]);
			free (philos);
			return (0);
		}
		init_philo (philos[i], data, i);
	}
	return (philos);
}

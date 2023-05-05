/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:08:58 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/27 15:08:59 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_itoa(int n)
{
	char	*tmp;
	int		len_n;

	if (n == 0)
		len_n = 1;
	else if (n == -2147483648)
		len_n = 11;
	else
		len_n = ft_len(n);
	tmp = (char *)malloc(sizeof(char) * len_n + 1);
	if (tmp == 0)
		return (0);
	ft_putnbr (tmp, n, len_n);
	tmp[len_n] = '\0';
	return (tmp);
}

void	ft_putnbr(char *s, int n, int len_n)
{
	if (n == 0)
		s[0] = '0';
	else if (n < 0)
	{
		if (n == -2147483648)
		{
			s[0] = '-';
			recursion (&s[1], (n / 10) * -1, len_n - 3);
			s[10] = '8';
			return ;
		}
		n *= -1;
		s[0] = '-';
		recursion (&s[1], n, len_n - 2);
	}
	else
		recursion (s, n, len_n - 1);
}

void	recursion(char *s, int n, int len_n)
{
	char	c;

	if (n == 0)
		return ;
	recursion (s, n / 10, len_n - 1);
	c = (n % 10) + '0';
	s[len_n] = c;
}

int	ft_len(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

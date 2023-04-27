/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang2 <jhwang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:08:54 by jhwang2           #+#    #+#             */
/*   Updated: 2023/04/27 15:08:55 by jhwang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*p_calloc(size_t count, size_t size)
{
	void	*result;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	result = (void *) malloc(size * count);
	if (result == 0)
		return (0);
	p_bzero(result, size * count);
	return (result);
}

void	p_bzero(void *dest, size_t size)
{
	size_t			i;
	unsigned char	*c_dest;

	i = 0;
	c_dest = (unsigned char *) dest;
	while (i < size)
	{
		c_dest[i] = 0;
		i++;
	}
}

int	p_atoi(const char *str)
{
	size_t					i;
	unsigned long long		result;
	int						sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if ((result > 9223372036854775807) && (sign == 1))
			return (-1);
		if ((result > 9223372036854775808UL) && (sign == -1))
			return (0);
		i++;
	}
	return (((int) result) * sign);
}

size_t	p_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	p_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	len_dns;
	size_t	size;

	len_src = 0;
	len_dst = 0;
	while (src[len_src] != '\0')
		len_src++;
	while (dst[len_dst] != '\0')
		len_dst++;
	len_dns = len_dst + len_src;
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	size = dstsize - len_dst - 1;
	while (*src != '\0' && size > 0)
	{
		dst[len_dst] = *src;
		src++;
		len_dst++;
		size--;
	}
	dst[len_dst] = '\0';
	return (len_dns);
}

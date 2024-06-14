/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:04:31 by glions            #+#    #+#             */
/*   Updated: 2024/06/14 11:37:16 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	ft_ltoa_len(long long n)
{
	int	i;
	int	m;

	i = 1;
	m = 1;
	while (n / m >= 10)
	{
		m *= 10;
		i++;
	}
	return (i);
}

char	*ft_ltoa(long n)
{
	char		*s;
	int 		i;
	int 		j;
	long long	nb;

	nb = n;
	if (nb > LONG_MAX || nb < 0)
		return (NULL);
	i = ft_ltoa_len(nb);
	s = (char *)malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	j = i;
	while (--j >= 0)
	{
		s[j] = (nb % 10) + '0';
		nb /= 10;
	}
	s[i] = '\0';
	return (s);
}
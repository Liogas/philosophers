/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:03:18 by glions            #+#    #+#             */
/*   Updated: 2024/05/24 15:38:02 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	ft_itoa_len(int n)
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

char	*ft_itoa(int n)
{
	long 	nb;
	char	*s;
	int		i;
	int		j;

	nb = n;
	if (nb < 0 || nb > INT_MAX)
		return (NULL);
	i = ft_itoa_len(nb);
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

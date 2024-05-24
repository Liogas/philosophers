/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:50:25 by glions            #+#    #+#             */
/*   Updated: 2024/05/24 15:43:50 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	v;

	i = 0;
	n = 1;
	v = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			n = -1;
	while (ft_isdigit(nptr[i]))
		v = (v * 10) + nptr[i++] - '0';
	return (v * n);
}

long	ft_atol(const char *nptr)
{
	int		i;
	int		n;
	long	v;

	i = 0;
	n = 1;
	v = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			n = -1;
	while (ft_isdigit(nptr[i]))
		v = (v * 10) + nptr[i++] - '0';
	return (v * n);
}

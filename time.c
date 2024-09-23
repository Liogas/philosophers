/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:35:55 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 10:36:04 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;
	long long		value;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	value = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (value);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:28:58 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 15:36:47 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg(char *msg, t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->mutex.philo)))
		return (0);
	if (philo->state)
		return (pthread_mutex_unlock(&(philo->mutex.philo)), 0);
	if (pthread_mutex_unlock(&(philo->mutex.philo)))
		return (0);
	if (pthread_mutex_lock(philo->mutex.print))
		return (0);
	printf("%lld %d %s\n", get_time() - philo->time_start, philo->id, msg);
	if (pthread_mutex_unlock(philo->mutex.print))
		return (0);
	return (1);
}

void	print_death(t_philo *philo)
{
	if (pthread_mutex_lock(philo->mutex.print))
		return ;
	printf("%lld %d died\n", get_time() - philo->time_start, philo->id);
	pthread_mutex_unlock(philo->mutex.print);
}

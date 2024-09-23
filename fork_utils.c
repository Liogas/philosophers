/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:12:59 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 18:05:12 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo, t_fork *fork)
{
	int	v;

	v = 0;
	if (pthread_mutex_lock(&(fork->mutex)))
		return (-1);
	if ((fork->last == 0 || fork->last != philo->id) && fork->state == 0)
	{
		fork->state = 1;
		v = 1;
	}
	if (pthread_mutex_unlock(&(fork->mutex)))
		return (-1);
	return (v);
}

int	take_forks2(t_philo *philo, int	*v)
{
	*v = take_fork(philo, philo->fork_r);
	if (*v == -1)
		return (leave_fork(philo, philo->fork_l, 0), -1);
	if (!*v)
		leave_fork(philo, philo->fork_l, 0);
	return (*v);
}

int	take_forks(t_philo *philo)
{
	int	v;

	v = 0;
	while (!v)
	{
		if (pthread_mutex_lock(&(philo->mutex.philo)))
			return (0);
		if (philo->state)
			return (pthread_mutex_unlock(&(philo->mutex.philo)), 0);
		if (pthread_mutex_unlock(&(philo->mutex.philo)))
			return (0);
		v = take_fork(philo, philo->fork_l);
		if (v == -1)
			return (0);
		if (v && take_forks2(philo, &v) == -1)
			return (0);
		usleep(500);
	}
	if (!print_msg("has taken a fork", philo) || !print_msg("has taken a fork",
			philo))
		return (leave_fork(philo, philo->fork_l, 0), leave_fork(philo,
				philo->fork_r, 0), 0);
	return (1);
}

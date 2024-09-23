/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:36:43 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 18:05:08 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	routine_sleep(t_philo *philo)
{
	long long	time;

	if (!print_msg("is sleeping", philo))
		return (0);
	time = get_time();
	while (get_time() - time < philo->rule.tts)
	{
		if (pthread_mutex_lock(&(philo->mutex.philo)))
			return (0);
		if (philo->state)
			return (pthread_mutex_unlock(&(philo->mutex.philo)), 0);
		if (pthread_mutex_unlock(&(philo->mutex.philo)))
			return (0);
		usleep(500);
	}
	return (1);
}

static int	routine_eat2(t_philo *philo, long long time)
{
	while (get_time() - time < philo->rule.tte)
	{
		if (pthread_mutex_lock(&(philo->mutex.philo)))
			return (leave_fork(philo, philo->fork_l, 0), leave_fork(philo,
					philo->fork_r, 0), 0);
		if (philo->state)
			return (pthread_mutex_unlock(&(philo->mutex.philo)), 0);
		if (pthread_mutex_unlock(&(philo->mutex.philo)))
			return (leave_fork(philo, philo->fork_l, 0), leave_fork(philo,
					philo->fork_r, 0), 0);
		usleep(500);
	}
	return (1);
}

static int	routine_eat(t_philo *philo)
{
	long long	time;

	if (!take_forks(philo))
		return (0);
	if (!print_msg("is eating", philo))
		return (leave_fork(philo, philo->fork_l, 0), leave_fork(philo,
				philo->fork_r, 0), 0);
	if (pthread_mutex_lock(&(philo->mutex.philo)))
		return (leave_fork(philo, philo->fork_l, 0), leave_fork(philo,
				philo->fork_r, 0), 0);
	philo->last_meal = get_time();
	philo->count_meal += 1;
	time = philo->last_meal;
	if (pthread_mutex_unlock(&(philo->mutex.philo)))
		return (leave_fork(philo, philo->fork_l, 0), leave_fork(philo,
				philo->fork_r, 0), 0);
	if (!routine_eat2(philo, time))
		return (0);
	(leave_fork(philo, philo->fork_l, 1), leave_fork(philo, philo->fork_r, 1));
	return (1);
}

static void	start_routine(t_philo *philo)
{
	if (philo->rule.nbp == 1)
	{
		if (pthread_mutex_lock(&(philo->mutex.philo)))
			return ;
		while (!philo->state)
		{
			if (pthread_mutex_unlock(&(philo->mutex.philo)))
				return ;
			usleep(philo->rule.ttd * 1000);
			if (pthread_mutex_lock(&(philo->mutex.philo)))
				return ;
		}
		if (pthread_mutex_unlock(&(philo->mutex.philo)))
			return ;
		return ;
	}
	while (1)
	{
		if (!routine_eat(philo) || !routine_sleep(philo))
			return ;
		if (!print_msg("is thinking", philo))
			return ;
		usleep(50);
	}
}

void	*waiting_room(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (pthread_mutex_lock(philo->mutex.print))
		return (NULL);
	while (philo->time_start == 0)
	{
		if (pthread_mutex_unlock(philo->mutex.print))
			return (NULL);
		usleep(1);
		if (pthread_mutex_lock(philo->mutex.print))
			return (0);
	}
	if (pthread_mutex_unlock(philo->mutex.print))
		return (0);
	if (philo->id % 2 != 0)
		usleep(philo->rule.tte * 1000);
	if (philo->id % 2 != 0 && philo->id == philo->rule.nbp)
		usleep(philo->rule.tte * 1000);
	start_routine(philo);
	return (NULL);
}

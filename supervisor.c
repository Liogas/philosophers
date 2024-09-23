/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:23:04 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 18:04:49 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_philo(t_core *core_dt)
{
	int	i;

	i = -1;
	while (++i < core_dt->rule.nbp)
	{
		if (pthread_mutex_lock(&((core_dt->philos)[i]->mutex.philo)))
			return ;
		(core_dt->philos)[i]->state = 1;
		if (pthread_mutex_unlock(&((core_dt->philos)[i]->mutex.philo)))
			return ;
	}
}

static int	verif_dead(t_core *core_dt)
{
	int	i;

	i = -1;
	while (++i < core_dt->rule.nbp)
	{
		if (pthread_mutex_lock(&((core_dt->philos)[i]->mutex.philo)))
			return (-1);
		if (get_time() - (core_dt->philos)[i]->last_meal >= core_dt->rule.ttd)
			return (pthread_mutex_unlock(&((core_dt->philos)[i]->mutex.philo)),
				print_death((core_dt->philos)[i]), stop_philo(core_dt), 1);
		if (pthread_mutex_unlock(&((core_dt->philos)[i]->mutex.philo)))
			return (-1);
	}
	return (0);
}

static int	verif_meal(t_core *core_dt)
{
	int	i;
	int	meal;

	i = -1;
	meal = 0;
	while (++i < core_dt->rule.nbp)
	{
		if (pthread_mutex_lock(&((core_dt->philos)[i]->mutex.philo)))
			return (-1);
		if (core_dt->rule.nbe != -1
			&& (core_dt->philos)[i]->count_meal >= core_dt->rule.nbe)
			meal += 1;
		if (pthread_mutex_unlock(&((core_dt->philos)[i]->mutex.philo)))
			return (-1);
	}
	if (meal == core_dt->rule.nbp)
		return (stop_philo(core_dt), 1);
	return (0);
}

static int	start_philos(t_core *core_dt)
{
	int	i;

	if (pthread_mutex_lock(&core_dt->print))
		return (0);
	core_dt->time_start = get_time();
	i = -1;
	while (++i < core_dt->rule.nbp)
	{
		((core_dt->philos)[i])->time_start = core_dt->time_start;
		((core_dt->philos)[i])->last_meal = core_dt->time_start;
	}
	if (pthread_mutex_unlock(&core_dt->print))
		return (0);
	return (1);
}

void	*supervisor(void *arg)
{
	t_core	*core_dt;
	int		i;
	int		v;

	core_dt = (t_core *)arg;
	if (!start_philos(core_dt))
		return (NULL);
	i = -1;
	v = 0;
	while (!v)
	{
		v = verif_dead(core_dt);
		if (v == -1)
			return (NULL);
		if (!v)
			v = verif_meal(core_dt);
		if (v == -1)
			return (NULL);
		usleep(250);
	}
	return (NULL);
}

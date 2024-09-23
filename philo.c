/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:18:54 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 17:27:45 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_up_mutex(t_philo_mutex *mutex, t_core *core_dt)
{
	mutex->print = &(core_dt->print);
	if (!init_mutex(&(mutex->philo)))
		return (0);
	return (1);
}

static t_philo	*create_philo(t_core *core_dt, int id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = -1;
	new->state = 0;
	new->last_meal = 0;
	new->count_meal = 0;
	new->rule = core_dt->rule;
	new->time_start = 0;
	new->fork_l = NULL;
	new->fork_r = NULL;
	if (!set_up_mutex(&(new->mutex), core_dt))
		return (free(new), NULL);
	new->id = id;
	return (new);
}

int	set_up_philos(t_core *core_dt)
{
	int	i;

	core_dt->util = 0;
	core_dt->philos = malloc(core_dt->rule.nbp * sizeof(t_philo));
	if (!core_dt->philos)
		return (0);
	i = -1;
	while (++i < core_dt->rule.nbp)
	{
		(core_dt->philos)[i] = create_philo(core_dt, i + 1);
		if (!(core_dt->philos)[i])
			return (free_core(core_dt, 1), 0);
		core_dt->util += 1;
	}
	return (1);
}

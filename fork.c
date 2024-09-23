/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:19:43 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 17:27:57 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leave_fork(t_philo *philo, t_fork *fork, int mode)
{
	if (pthread_mutex_lock(&(fork->mutex)))
		return ;
	fork->state = 0;
	if (mode)
		fork->last = philo->id;
	if (pthread_mutex_unlock(&(fork->mutex)))
		return ;
}

void	assign_forks(t_core *core_dt)
{
	int	i;

	i = -1;
	while (++i < core_dt->rule.nbp)
	{
		(core_dt->philos)[i]->fork_r = (core_dt->forks)[i];
		if (i + 1 >= core_dt->rule.nbp)
			(core_dt->philos)[i]->fork_l = (core_dt->forks)[0];
		else
			(core_dt->philos)[i]->fork_l = (core_dt->forks)[i + 1];
	}
}

static t_fork	*create_fork(void)
{
	t_fork	*new;

	new = malloc(sizeof(t_fork));
	if (!new)
		return (NULL);
	new->state = 0;
	new->last = 0;
	if (!init_mutex(&new->mutex))
		return (free(new), NULL);
	return (new);
}

int	set_up_forks(t_core *core_dt)
{
	int	i;

	core_dt->util = 0;
	core_dt->forks = malloc(core_dt->rule.nbp * sizeof(t_philo *));
	if (!core_dt->forks)
		return (0);
	i = -1;
	while (++i < core_dt->rule.nbp)
	{
		(core_dt->forks)[i] = create_fork();
		if (!(core_dt->forks)[i])
			return (free_core(core_dt, 2), 0);
		core_dt->util += 1;
	}
	return (1);
}

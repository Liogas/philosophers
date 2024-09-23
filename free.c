/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:28:32 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 10:30:11 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:13:47 by glions            #+#    #+#             */
/*   Updated: 2024/09/13 12:45:00 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	del_forks(t_fork **forks, int limit)
{
	int	i;

	i = -1;
	while (++i < limit)
		(destroy_mutex(&((forks[i])->mutex)), free(forks[i]));
	free(forks);
}

static void	del_philos(t_philo **philos, int limit)
{
	int	i;

	i = -1;
	while (++i < limit)
	{
		if ((philos[i])->id != -1)
			(destroy_mutex(&(philos[i])->mutex.philo));
		free(philos[i]);
	}
	free(philos);
}

void	free_core(t_core *core_dt, int mode)
{
	if (core_dt->mutex_create)
		(destroy_mutex(&(core_dt->print)));
	if (core_dt->forks)
	{
		if (mode == 2)
			del_forks(core_dt->forks, core_dt->util);
		else
			del_forks(core_dt->forks, core_dt->rule.nbp);
	}
	if (core_dt->philos)
	{
		if (mode == 1)
			del_philos(core_dt->philos, core_dt->util);
		else
			del_philos(core_dt->philos, core_dt->rule.nbp);
	}
	if (core_dt->threads)
		free(core_dt->threads);
	free(core_dt);
}

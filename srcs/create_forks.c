/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:32:49 by glions            #+#    #+#             */
/*   Updated: 2024/05/25 16:17:02 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_tab(t_fork	**tab, int size)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (++i < size)
		{
			pthread_mutex_destroy(&tab[i]->mutex);
			free(tab[i]);
		}
		free(tab);
	}
}

static t_fork	*create_fork(void)
{
	t_fork	*new;

	new = malloc(sizeof(t_fork));
	if (!new)
		return (NULL);
	new->in_table = 1;
	if (pthread_mutex_init(&new->mutex, NULL))
		return (free(new), NULL);
	return (new);
}

static int	assign_forks(t_dt *dt, t_fork **tab)
{
	int				i;
	t_node_philo	*philo;

	i = -1;
	philo = dt->philos;
	while (++i < dt->nbp && philo)
	{
		philo->dt->fr = tab[i];
		if (i + 1 >= dt->nbp)
			philo->dt->fl = tab[0];
		else
			philo->dt->fl = tab[i + 1]; 
		philo = philo->left;
	}
	return (1);
}

int	init_forks(t_dt	*dt)
{
	int		i;
	t_fork	**tab;

	tab = malloc(dt->nbp * sizeof(t_fork *));
	if (!tab)
		return (0);
	i = -1;
	while (++i < dt->nbp)
	{
		tab[i] = create_fork();
		if (!tab[i])
			return (free_tab(tab, dt->nbp), 0);
	}
	if (!assign_forks(dt, tab))
		return (free_tab(tab, dt->nbp), 0);
	free(tab);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:36:01 by glions            #+#    #+#             */
/*   Updated: 2024/05/24 18:00:08 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_node_philo *philos)
{
	t_node_philo	*tmp;

	while (philos)
	{
		tmp = philos->left;
		free(philos);
		philos = tmp;
	}
}

static t_philo	*create_dt(t_config_philo *c)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->config = c;
	new->fl = NULL;
	new->rl = NULL;
	new->status = 0;
	new->time_last_eat = 0;
	new->time_start = 0;
	return (new);
}

t_node_philo	*create_philo(t_node_philo *left, int id, t_config_philo *c)
{
	t_node_philo	*new;

	new = malloc(sizeof(t_node_philo));
	if (!new)
		return (NULL);
	if (left)
		left->right = new;
	new->id = id;
	new->right = NULL;
	new->dt = create_dt(c);
	if (!new->dt)
		return (free(new), NULL);
	new->left = left;
	return (new);
}

t_node_philo	*create_philos(t_dt *dt)
{
	t_node_philo *first;
	t_node_philo *prev;
	int		i;

	first = create_philo(NULL, 1, dt->config);
	if (!first)
		return (NULL);
	i = 1;
	prev = first;
	while (++i < dt->nbp)
	{
		prev = create_philo(prev, i, dt->config);
		if (!prev)
			return (free_philos(first), NULL);
	}
	if (!create_philo(first, i, dt->config))
		return (free_philos(first), NULL);
	return (first);
}

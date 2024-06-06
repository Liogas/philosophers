/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:36:01 by glions            #+#    #+#             */
/*   Updated: 2024/06/06 10:03:04 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo	*dt)
{
	if (dt)
	{
		if (dt->config)
			free(dt->config);
		free(dt);
	}
}

void	free_philos(t_node_philo *philos, int size)
{
	t_node_philo	*tmp;
	int				i;

	i = -1;
	while (++i < size && philos)
	{
		tmp = philos->left;
		pthread_mutex_destroy(&philos->dt->fl->mutex);
		free_philo(philos->dt);
		free(philos);
		philos = tmp;
	}
}

static t_philo	*create_philo_dt(t_config_philo *c, int id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->config = c;
	new->id = id;
	new->fl = NULL;
	new->fr = NULL;
	new->exit_value = 0;
	new->time = -1;
	new->status = 0;
	new->time_last_eat = c->ttd;
	return (new);
}

static t_node_philo	*create_philo(t_node_philo **right, int id, t_config_philo *c)
{
	t_node_philo	*new;

	new = malloc(sizeof(t_node_philo));
	if (!new)
		return (NULL);
	new->dt = create_philo_dt(c, id);
	if (!new->dt)
		return (free(new), NULL);
	new->left = NULL;
	new->right = NULL;
	if (right && *right)
	{
		(*right)->left = new;
		new->right = *right;
	}
	return (new);
}

t_node_philo	*create_philos(t_dt *dt)
{
	t_node_philo	*node;
	t_node_philo	*first;
	int				i;

	first = create_philo(NULL, 1, dup_config(dt->config));
	if (!first)
		return (NULL);
	i = 1;
	node = first;
	while (++i < dt->nbp + 1 && node)
	{
		node = create_philo(&node, i, dup_config(dt->config));
		if (!node)
			return (free_philos(first, dt->nbp), NULL);
	}
	node->left = first;
	first->right = node;
	return (first);
}

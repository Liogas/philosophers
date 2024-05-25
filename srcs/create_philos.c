/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:36:01 by glions            #+#    #+#             */
/*   Updated: 2024/05/25 16:14:14 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_node_philo *philos, int size)
{
	t_node_philo	*tmp;
	int				i;

	i = -1;
	while (++i < size && philos)
	{
		tmp = philos->left;
		pthread_mutex_destroy(&philos->dt->fl->mutex);
		free(philos->dt->fl);
		free(philos->dt);
		free(philos);
		philos = tmp;
	}
}

static t_philo	*create_dt(t_config_philo **c)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->config = *c;
	new->fl = NULL;
	new->fr = NULL;
	new->status = 0;
	new->time_last_eat = (*c)->ttd;
	return (new);
}

static t_node_philo	*create_philo(t_node_philo **right, int id, t_config_philo **c)
{
	t_node_philo	*new;

	new = malloc(sizeof(t_node_philo));
	if (!new)
		return (NULL);
	new->dt = create_dt(c);
	if (!new->dt)
		return (free(new), NULL);
	new->left = NULL;
	new->right = NULL;
	new->id = id;
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

	first = create_philo(NULL, 1, &dt->config);
	if (!first)
		return (NULL);
	i = 1;
	node = first;
	while (++i < dt->nbp + 1 && node)
	{
		node = create_philo(&node, i, &dt->config);
		if (!node)
			return (free_philos(first, dt->nbp), NULL);
	}
	node->left = first;
	first->right = node;
	return (first);
}

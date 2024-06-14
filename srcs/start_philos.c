/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:31:06 by glions            #+#    #+#             */
/*   Updated: 2024/06/14 11:58:04 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_time_start(t_dt *dt)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		dt->config->time_start->value = -2;
		return (0);
	}
	dt->config->time_start->value = (time.tv_sec * 1000000) + time.tv_usec;
	return (1);
}

int	start_philos(t_dt *dt)
{
	int				i;
	t_node_philo	*p;

	dt->threads = malloc(dt->nbp * sizeof(pthread_t));
	if (!dt->threads)
		return (0);
	i = -1;
	p = dt->philos;
	while (++i < dt->nbp && p)
	{
		if (pthread_create(&dt->threads[i], NULL, ft_philo, p->dt))
			return (printf("ERROR IIIICIII\n"), free(dt->threads), 0);
		p = p->left;
	}
	i = -1;
	pthread_mutex_lock(&dt->config->time_start->mutex);
	if (!set_time_start(dt))
		return (pthread_mutex_unlock(&dt->config->time_start->mutex), 0);
	pthread_mutex_unlock(&dt->config->time_start->mutex);
	return (1);
}

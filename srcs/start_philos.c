/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:31:06 by glions            #+#    #+#             */
/*   Updated: 2024/05/25 23:06:33 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_time_start(t_dt *dt)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		dt->config->time_start = -2;
		return ;
	}
	dt->config->time_start = (time.tv_sec * 1000000) + time.tv_usec;
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
	pthread_mutex_lock(&dt->config->mutex_time);
	set_time_start(dt);
	pthread_mutex_unlock(&dt->config->mutex_time);
	return (1);
}

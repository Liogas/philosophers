/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:20:47 by glions            #+#    #+#             */
/*   Updated: 2024/06/14 14:32:11 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait(t_philo	*p)
{
	while (1)
	{
		if (pthread_mutex_lock(&p->config->time_start->mutex))
			perror("");
		else
		{
			if (p->config->time_start->value == -1)
				printf("Philo[%d] : En attente\n", p->id);
			else
			{
				if (p->config->time_start->value == -2)
					printf("Philo[%d] : Error set time\n", p->id);
				if (pthread_mutex_unlock(&p->config->time_start->mutex))
					perror("");
				break ;
			}
		if (pthread_mutex_unlock(&p->config->time_start->mutex))
			perror("");
		}
	}
}

int	update_time(t_philo *p)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	p->time = ((time.tv_sec * 1000000) + time.tv_usec) - p->config->time_start->value;
	return (1);
}

int	ft_routine(t_philo *p)
{
	if (!update_time(p))
		return (0);
	// printf("%ld > %ld - (%ld * 2)(%ld)\n", p->time / 1000, p->config->ttd, p->config->tte, p->config->tte * 2);
	if (p->time / 1000 > p->config->ttd - (p->config->tte * 2))
	{
		pthread_mutex_lock(&p->fl->mutex);
		if (!update_time(p))
			return (0);
		pthread_mutex_lock(&p->config->out->mutex);
		printf("%ld %d has taken a fork\n", p->time / 1000, p->id);
		pthread_mutex_unlock(&p->config->out->mutex);
		pthread_mutex_lock(&p->fr->mutex);
		if (!update_time(p))
			return (0);
		pthread_mutex_lock(&p->config->out->mutex);
		printf("%ld %d has taken a fork\n", p->time / 1000, p->id);
		pthread_mutex_unlock(&p->config->out->mutex);
		if (!update_time(p))
			return (0);
		pthread_mutex_lock(&p->config->out->mutex);
		printf("%ld %d is eating\n", p->time / 1000, p->id);
		pthread_mutex_unlock(&p->config->out->mutex);
		usleep(p->config->tte);
		pthread_mutex_unlock(&p->fl->mutex);
		pthread_mutex_unlock(&p->fr->mutex);
		if (!update_time(p))
			return (0);
		pthread_mutex_lock(&p->config->out->mutex);
		printf("%ld %d is sleeping\n", p->time / 1000, p->id);
		pthread_mutex_unlock(&p->config->out->mutex);
		usleep(p->config->tts);
		if (!update_time(p))
			return (0);
		pthread_mutex_lock(&p->config->out->mutex);
		printf("%ld %d is thinking\n", p->time / 1000, p->id);
		pthread_mutex_unlock(&p->config->out->mutex);
	}
	return (1);
}

void	*ft_philo(void *philo)
{
	t_philo	*p;
	int		e;

	p = philo;
	if (!p)
		return (NULL);
	ft_wait(p);
	if (!update_time(p))
		return (NULL);
	pthread_mutex_lock(&p->config->out->mutex);
	if (!p->config->out->value)
	{
		p->config->out->value = 1;
		printf("Philo[%d] : Pret à l'emploi (lancement après %ld.%ld ms)\n", p->id, p->time / 1000, p->time % 1000);
	}
	p->config->out->value = 0;
	pthread_mutex_unlock(&p->config->out->mutex);
	e = 1;
	while (e)
	{
		printf("Nouveau tour\n");
		e = ft_routine(p);
	}
	p->exit_value = 1;
	return ("OK");
}

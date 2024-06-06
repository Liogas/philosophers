/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:20:47 by glions            #+#    #+#             */
/*   Updated: 2024/06/06 09:48:21 by glions           ###   ########.fr       */
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

void	*ft_philo(void *philo)
{
	t_philo			*p;
	struct timeval	time;

	p = philo;
	if (!p)
		return (NULL);
	ft_wait(p);
	if (gettimeofday(&time, NULL) == -1)
		return (NULL);
	p->time = ((time.tv_sec * 1000000) + time.tv_usec) - p->config->time_start->value;
	pthread_mutex_lock(&p->config->out->mutex);
	if (!p->config->out->value)
	{
		p->config->out->value = 1;
		printf("Philo[%d] : Pret à l'emploi (lancement après %ld.%ld ms)\n", p->id, p->time / 1000, p->time % 1000);
	}
	p->config->out->value = 0;
	pthread_mutex_unlock(&p->config->out->mutex);
	usleep(5000000);
	if (gettimeofday(&time, NULL) == -1)
		return (NULL);
	p->time = ((time.tv_sec * 1000000) + time.tv_usec) - p->config->time_start->value;
	printf("Philo[%d] : Apres pause de 5000 ms (%ld.%ld ms)\n", p->id, p->time / 1000, p->time % 1000);
	p->exit_value = 1;
	return ("OK");
}

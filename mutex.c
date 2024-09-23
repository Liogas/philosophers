/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:25:42 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 10:25:46 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(pthread_mutex_t *mutex)
{
	if (mutex && pthread_mutex_destroy(mutex))
		return (perror("destroy_mutex:"), 0);
	return (1);
}

int	init_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL))
		return (perror("init_mutex:"), 0);
	return (1);
}

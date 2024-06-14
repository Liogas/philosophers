/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:31:47 by glions            #+#    #+#             */
/*   Updated: 2024/06/14 11:40:05 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_dt(t_dt *dt)
{
	if (dt)
	{
		if (dt->philos)
			free_philos(dt->philos, dt->nbp);
		if (dt->config)
			free_config(dt->config);
		if (dt->threads)
			free(dt->threads);
		if (dt->forks)
			free_forks(dt->forks, dt->nbp);
		free(dt);
	}
}

t_dt	*create_dt(char **av, int ac)
{
	t_dt	*dt;

	dt = malloc(sizeof(t_dt));
	if (!dt)
		return (NULL);
	dt->nbp = ft_atoi(av[0]);
	dt->config = create_config(av + 1, ac - 1);
	if (!dt->config)
		return (free(dt), NULL);
	dt->threads = NULL;
	dt->philos = create_philos(dt);
	if (!dt->philos)
		return (free(dt->config), free(dt), NULL);
	printf("AVANT INIT FORK\n");
	print_all_dt(dt, ac);
	if (!init_forks(dt))
		return (free_philos(dt->philos, dt->nbp), free(dt->config), NULL);
	printf("APRES INIT FORK\n");
	print_all_dt(dt, ac);
	return (dt);
}

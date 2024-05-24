/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:26:48 by glions            #+#    #+#             */
/*   Updated: 2024/05/24 17:50:44 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	error_args(void)
{
	write(2, "Try ./philo [number_of_philo] [time_to_die]", 122);
	write(2, " [time_to_eat] [time_to_sleep]", 30);
	write(2, " [number_of_times_each_philo_must_eat](optional)\n", 49);
	return (1);
}



t_dt	*create_dt(char **av, int ac)
{
	t_dt	*dt;
	t_node_philo	*philo;
	t_philo		*dt_philo;

	dt = malloc(sizeof(t_dt));
	if (!dt)
		return (NULL);
	dt->nbp = ft_atoi(av[0]);
	dt->config = create_config(av + 1, ac - 1);
	if (!dt->config)
		return (free(dt), NULL);
	dt->philos = create_philos(dt);
	if (!dt->philos)
		return (free(dt->config), free(dt), NULL);
	printf("dt->nbp->%d\n", dt->nbp);
	printf("Config :\n");
	printf("ttd->%ld\n", dt->config->ttd);
	printf("tte->%ld\n", dt->config->tte);
	printf("tts->%ld\n", dt->config->tts);
	printf("Philos :\n");
	philo = dt->philos;
	while (philo)
	{
		dt_philo = philo->dt;
		printf("Philo[%d]-> [left->%d; right->%d]\n", philo->id, philo->left->id, philo->right->id);
		printf("data->[fl->%p; rl->%p; status->%d; time_start->%ld; time_last_eat->%ld; config->%p]\n", dt_philo->fl, dt_philo->rl, dt_philo->status, dt_philo->time_start, dt_philo->time_last_eat, dt_philo->config);
		philo = philo->left;
	}
	return (dt);
}

int	main(int ac, char **av)
{
	t_dt	*dt;

	if (ac < 5 || ac > 6)
		return (error_args());
	dt = create_dt(av + 1, ac - 1);
	if (!dt)
		return (write(2, "ERROR init_dt\n", 14), 1);
	free(dt->config);
	free(dt);
	return (0);
}

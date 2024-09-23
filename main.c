/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:13:23 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 17:26:36 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_threads(t_core *core_dt)
{
	int	i;

	i = -1;
	while (++i < core_dt->rule.nbp)
	{
		if (pthread_join((core_dt->threads)[i], NULL))
			return (perror("wait_threads:"), 0);
	}
	return (1);
}

static int	start_simulation(t_core *core_dt)
{
	int			i;
	pthread_t	sup;

	core_dt->threads = malloc(core_dt->rule.nbp * sizeof(pthread_t *));
	if (!core_dt->threads)
		return (0);
	i = -1;
	while (++i < core_dt->rule.nbp)
		if (pthread_create(&(core_dt->threads)[i], NULL, &waiting_room,
			(core_dt->philos[i])))
			return (0);
	if (pthread_create(&sup, NULL, &supervisor, core_dt))
		return (0);
	if (pthread_join(sup, NULL))
		return (0);
	return (1);
}

static int	parsing(int ac, char **av, t_core *core_dt)
{
	core_dt->rule.nbp = ft_atoi(av[1]);
	core_dt->rule.ttd = ft_atoi(av[2]);
	core_dt->rule.tte = ft_atoi(av[3]);
	core_dt->rule.tts = ft_atoi(av[4]);
	core_dt->rule.nbe = -1;
	if (ac == 6)
	{
		core_dt->rule.nbe = ft_atoi(av[5]);
		if (core_dt->rule.nbe <= 0 || !verif_conv(core_dt->rule.nbe, av[5]))
			return (0);
	}
	if (core_dt->rule.nbp <= 0 || !verif_conv(core_dt->rule.nbp, av[1])
		|| core_dt->rule.ttd <= 0 || !verif_conv(core_dt->rule.ttd, av[2])
		|| core_dt->rule.tte <= 0 || !verif_conv(core_dt->rule.tte, av[3])
		|| core_dt->rule.tts <= 0 || !verif_conv(core_dt->rule.tts, av[4]))
		return (0);
	if (!init_mutex(&(core_dt->print)))
		return (0);
	core_dt->mutex_create = 1;
	return (1);
}

int	main(int ac, char **av)
{
	t_core	*core_dt;

	if (ac < 5 || ac > 6)
		return (write(2, "Error args\n", 11), 1);
	core_dt = malloc(sizeof(t_core));
	core_dt->mutex_create = 0;
	core_dt->util = 0;
	core_dt->forks = NULL;
	core_dt->philos = NULL;
	core_dt->threads = NULL;
	if (!core_dt)
		return (1);
	if (!parsing(ac, av, core_dt))
		return (free_core(core_dt, 0), write(2, "Error parsing\n", 14), 1);
	if (!set_up_forks(core_dt))
		return (write(2, "Error set_up_forks\n", 19), 1);
	if (!set_up_philos(core_dt))
		return (write(2, "Error set_up_philos\n", 20), 1);
	assign_forks(core_dt);
	if (!start_simulation(core_dt) || !wait_threads(core_dt))
		return (free_core(core_dt, 0), write(2, "Error start_simulation\n", 23),
			1);
	return (free_core(core_dt, 0), 0);
}

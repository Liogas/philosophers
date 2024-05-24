/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:26:48 by glions            #+#    #+#             */
/*   Updated: 2024/05/24 11:42:55 by glions           ###   ########.fr       */
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

t_dt	*init_dt(int ac, char **av)
{
	t_dt	*dt;

	(void)av;
	dt = malloc(sizeof(t_dt));
	if (!dt)
		return (NULL);
	dt->nbp = ac - 1;
	return (dt);
}

int	main(int ac, char **av)
{
	t_dt	*dt;

	if (ac < 5 || ac > 6)
		return (error_args());
	return (0);
	dt = init_dt(ac, av);
	if (!dt)
		return (write(2, "ERROR init_dt\n", 14), 1);
	return (0);
}

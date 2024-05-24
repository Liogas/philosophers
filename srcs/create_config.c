/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:45:55 by glions            #+#    #+#             */
/*   Updated: 2024/05/24 16:35:38 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_limit(char *av, t_config_philo *config)
{
	char	*str;
	int		e;

	e = 1;
	config->limit = ft_atoi(av);
	str = ft_itoa(config->limit);
	if (!str || ft_strcmp(av, str))
		e = 0;
	if (str)
		free(str);
	return (e);
}

int	get_long(char *nbr, long *value)
{
	char	*str;
	int		e;

	e = 1;
	*value = ft_atol(nbr);
	str = ft_ltoa(*value);
	if (!str || ft_strcmp(str, nbr))
		e = 0;
	if (str)
		free(str);
	return (e);
}

t_config_philo	*create_config(char **av, int ac)
{
	t_config_philo	*config;

	config = malloc(sizeof(t_config_philo));
	if (!config)
		return (NULL);
	if (!get_long(av[0], &config->ttd))
		return (free(config), NULL);
	if (!get_long(av[1], &config->tte))
		return (free(config), NULL);
	if (!get_long(av[2], &config->tts))
		return (free(config), NULL);
	if (ac == 4 && !get_limit(av[3], config))
		return (free(config), NULL);
	return (config);
}

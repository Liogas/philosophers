/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:45:55 by glions            #+#    #+#             */
/*   Updated: 2024/06/14 11:37:11 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_config_philo	*dup_config(t_config_philo *config)
{
	t_config_philo	*new;

	new = malloc(sizeof(t_config_philo));
	if (!new)
		return (NULL);
	new->limit = config->limit;
	new->ttd = config->ttd;
	new->tte = config->tte;
	new->tts = config->tts;
	new->time_start = config->time_start;
	new->out = config->out;
	return (new);
}

static int	get_limit(char *av, t_config_philo *config)
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

static int	get_long(char *nbr, long *value)
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

void	free_config(t_config_philo *dt)
{
	if (dt)
	{
		if (dt->time_start)
		{
			free(dt->time_start);
			dt->time_start = NULL;
		}
		if (dt->out)
		{
			free(dt->out);
			dt->out = NULL;
		}
		free(dt);
	}
}

t_config_philo	*create_config(char **av, int ac)
{
	t_config_philo	*config;

	config = malloc(sizeof(t_config_philo));
	if (!config)
		return (NULL);
	if (!get_long(av[0], &config->ttd) || !get_long(av[1], &config->tte))
		return (free(config), NULL);
	if (!get_long(av[2], &config->tts))
		return (free(config), NULL);
	if (ac == 4 && !get_limit(av[3], config))
		return (free(config), NULL);
	config->time_start = malloc(sizeof(t_time_start));
	if (!config->time_start)
		return (free(config), NULL);
	config->time_start->value = -1;
	if (pthread_mutex_init(&config->time_start->mutex, NULL))
		return (free_config(config), NULL);
	config->out = malloc(sizeof(t_stdout));
	if (!config->out)
		return (free_config(config), NULL);
	config->out->value = 0;
	if (pthread_mutex_init(&config->out->mutex, NULL))
		return (free_config(config), NULL);
	return (config);
}

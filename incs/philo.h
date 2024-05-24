/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:58:01 by glions            #+#    #+#             */
/*   Updated: 2024/05/24 11:41:53 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_config_philo
{
	const double		tss;
	const double		ttd;
	const double		tte;
	const int			limit;
}						t_config_philo;

typedef struct s_philo
{
	int					*fl;
	int					*rl;
	t_config_philo		*config;

}						t_philo;

typedef struct s_node_philo
{
	int					id;
	int					ttd;
	struct s_node_philo	*left;
	struct s_node_philo	*right;
}						t_node_philo;

typedef struct s_dt
{
	t_node_philo		*philos;
	t_config_philo		*config;
	int					nbp;
}						t_dt;

#endif
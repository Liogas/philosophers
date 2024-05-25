/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:58:01 by glions            #+#    #+#             */
/*   Updated: 2024/05/25 15:38:44 by glions           ###   ########.fr       */
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
	long				tts;
	long				ttd;
	long				tte;
	int					limit;
	long				time_start;
}						t_config_philo;

typedef struct s_fork
{
	int					in_table;
	pthread_mutex_t		mutex;
}						t_fork;

typedef struct s_philo
{
	t_fork				*fl;
	t_fork				*fr;
	int					status;
	long				time_last_eat;
	t_config_philo		*config;
}						t_philo;

typedef struct s_node_philo
{
	t_philo				*dt;
	int					id;
	struct s_node_philo	*left;
	struct s_node_philo	*right;
}						t_node_philo;

typedef struct s_dt
{
	t_node_philo		*philos;
	t_config_philo		*config;
	int					nbp;
}						t_dt;

t_config_philo			*create_config(char **av, int ac);
t_node_philo			*create_philos(t_dt *dt);
int						init_forks(t_dt *dt);

void					free_philos(t_node_philo *philos, int size);

// utils
int						ft_atoi(const char *nptr);
long					ft_atol(const char *nptr);
char					*ft_ltoa(long n);
char					*ft_itoa(int n);
int						ft_strcmp(char *s1, char *s2);
int						ft_isdigit(int c);

#endif
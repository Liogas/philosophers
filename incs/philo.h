/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:58:01 by glions            #+#    #+#             */
/*   Updated: 2024/06/14 11:39:48 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_time_start
{
	long				value;
	pthread_mutex_t		mutex;
}						t_time_start;

typedef struct s_stdout
{
	int					value;
	pthread_mutex_t		mutex;
}						t_stdout;

typedef struct s_config_philo
{
	long				tts;
	long				ttd;
	long				tte;
	int					limit;
	t_time_start		*time_start;
	t_stdout			*out;
}						t_config_philo;

typedef struct s_fork
{
	int					state;
	pthread_mutex_t		mutex;
}						t_fork;

typedef struct s_philo
{
	int					id;
	t_fork				*fl;
	t_fork				*fr;
	t_config_philo		*config;
	int					status;
	long				time_last_eat;
	int					exit_value;
	long				time;
}						t_philo;

typedef struct s_node_philo
{
	t_philo				*dt;
	struct s_node_philo	*left;
	struct s_node_philo	*right;
}						t_node_philo;

typedef struct s_dt
{
	t_node_philo		*philos;
	t_config_philo		*config;
	pthread_t			*threads;
	t_fork				**forks;
	int					nbp;
}						t_dt;

t_node_philo			*create_philos(t_dt *dt);
void					free_philos(t_node_philo *philos, int size);
int						start_philos(t_dt *dt);
void					*ft_philo(void *philo);

t_dt					*create_dt(char **av, int ac);
void					free_dt(t_dt *dt);

int						init_forks(t_dt *dt);
void					free_forks(t_fork **tab, int size);

t_config_philo			*dup_config(t_config_philo *config);
t_config_philo			*create_config(char **av, int ac);
void					free_config(t_config_philo *dt);

// utils
int						ft_atoi(const char *nptr);
long					ft_atol(const char *nptr);
char					*ft_ltoa(long n);
char					*ft_itoa(int n);
int						ft_strcmp(char *s1, char *s2);
int						ft_isdigit(int c);

void					print_all_dt(t_dt *dt, int ac);

#endif
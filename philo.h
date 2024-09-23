/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:55:32 by glions            #+#    #+#             */
/*   Updated: 2024/09/23 17:25:44 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				state;
	int				last;
}					t_fork;

typedef struct s_rule
{
	int				nbp;
	int				nbe;
	int				ttd;
	int				tte;
	int				tts;
}					t_rule;

typedef struct s_philo_mutex
{
	pthread_mutex_t	*print;
	pthread_mutex_t	philo;
}					t_philo_mutex;

typedef struct s_philo
{
	int				id;
	int				state;
	int				count_meal;
	long long		last_meal;
	long long		time_start;
	t_fork			*fork_l;
	t_fork			*fork_r;
	t_rule			rule;
	t_philo_mutex	mutex;
}					t_philo;

typedef struct s_core
{
	t_philo			**philos;
	t_fork			**forks;
	pthread_t		*threads;
	pthread_t		supervisor;
	t_rule			rule;
	pthread_mutex_t	print;
	long long		time_start;
	int				mutex_create;
	int				util;
}					t_core;

// philo.c
int					set_up_philos(t_core *core_dt);

// fork.c
void				assign_forks(t_core *core_dt);
int					set_up_forks(t_core *core_dt);

// fork_utils.c
void				leave_fork(t_philo *philo, t_fork *fork, int mode);
int					take_fork(t_philo *philo, t_fork *fork);
int					take_forks(t_philo *philo);

// routine.c
void				*waiting_room(void *arg);

// utils.c
int					ft_atoi(const char *nptr);
int					ft_strlen(char *string);
int					ft_isdigit(int c);
int					ft_strcmp(char *s1, char *s2);
int					ft_strlcpy(char *dst, const char *src, int size);

// ft_itoa.c
char				*ft_itoa(int n);
int					verif_conv(int nb, char *av);

// supervisor.c
void				*supervisor(void *arg);

// print.c
int					print_msg(char *msg, t_philo *philo);
void				print_death(t_philo *philo);

// free.c
void				free_core(t_core *core_dt, int mode);

// mutex.c
int					destroy_mutex(pthread_mutex_t *mutex);
int					init_mutex(pthread_mutex_t *mutex);

// time.c
long long			get_time(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:26:06 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/10 13:02:31 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_args
{
	int				nbr_philo;
	time_t			time_to_eat;
	time_t			time_to_die;
	time_t			time_to_sleep;
	int				nbr_time_must_eat;
	int				is_dead;
	int				nbr_eat;
	time_t			start;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_write;
}				t_args;

typedef struct s_philo
{
	int						id;
	pthread_t				thread;
	time_t					last_time_eat;
	pthread_mutex_t			*fork_r;
	pthread_mutex_t			fork_l;
	int						nbr_eat;
	t_args					*args;
}				t_philo;

typedef struct s_death
{
	t_args	*args;
	t_philo	**philos;
}				t_death;

int			ft_atoi(const char *s);
void		ft_usleep(long int time_in_ms, t_philo *philo);
long int	ft_actual_time(void);
void		ft_take_fork(t_philo *philo);
void		ft_died(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_write(char *str, t_philo *philo);
int			ft_check_args_negative(char **nbrs);
int			ft_error(int argc, char **argv);
int			ft_check_time(t_philo *philo);
int			ft_init_tab(t_philo *philos, t_args *args);
t_philo		ft_init_philo(int id, t_args *args);
int			ft_free(t_philo *philos, int i);
int			ft_destroy(t_args *args, t_philo *philos);
int			ft_check_digit(char *nbr);

#endif
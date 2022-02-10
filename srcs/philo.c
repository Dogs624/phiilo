/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:29:12 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/10 13:02:41 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_args	ft_init_args(int argc, char **argv)
{
	t_args	args;

	args.nbr_philo = ft_atoi(argv[1]);
	args.time_to_die = ft_atoi(argv[2]);
	args.time_to_eat = ft_atoi(argv[3]);
	args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args.nbr_time_must_eat = ft_atoi(argv[5]);
	else
		args.nbr_time_must_eat = -1;
	args.is_dead = 0;
	args.start = ft_actual_time();
	args.nbr_eat = 0;
	if (pthread_mutex_init(&args.mutex_write, NULL) == -1)
		args.nbr_philo = -1;
	if (pthread_mutex_init(&args.mutex_eat, NULL) == -1)
		args.nbr_philo = -1;
	if (pthread_mutex_init(&args.mutex_dead, NULL) == -1)
		args.nbr_philo = -1;
	return (args);
}

static int	ft_check_death(t_philo *philo)
{
	if (ft_actual_time() - philo->last_time_eat >= philo->args->time_to_die)
	{
		ft_died(philo);
		return (0);
	}
	pthread_mutex_lock(&philo->args->mutex_dead);
	pthread_mutex_lock(&philo->args->mutex_eat);
	if (!philo->args->is_dead && philo->args->nbr_eat < philo->args->nbr_philo)
	{
		pthread_mutex_unlock(&philo->args->mutex_dead);
		pthread_mutex_unlock(&philo->args->mutex_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->mutex_dead);
	pthread_mutex_unlock(&philo->args->mutex_eat);
	return (0);
}

void	*philosopher(void *philo_void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_void;
	i = 0;
	if (philo->args->nbr_philo == 1)
	{
		ft_usleep(philo->args->time_to_die, philo);
		ft_died(philo);
	}
	if (philo->id % 2)
		ft_usleep(10, philo);
	while (ft_check_death(philo))
	{
		ft_take_fork(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	ft_end(t_args *args, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < args->nbr_philo)
	{
		if (pthread_join(philos[i].thread, NULL) == -1)
			return (ft_free(philos, 7));
	}
	i = -1;
	pthread_mutex_lock(&args->mutex_dead);
	pthread_mutex_lock(&args->mutex_eat);
	if (args->is_dead || args->nbr_eat >= args->nbr_philo)
	{
		if (args->nbr_time_must_eat != -1 && args->nbr_eat >= args->nbr_philo)
		{
			pthread_mutex_lock(&args->mutex_write);
			printf("all philos have eaten at least %d times\n",
				args->nbr_time_must_eat);
			pthread_mutex_unlock(&args->mutex_write);
		}
		return (ft_destroy(args, philos));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo			*philos;
	int				i;

	if (ft_error(argc, argv))
		return (1);
	args = ft_init_args(argc, argv);
	if (args.nbr_philo < 1)
		return (2);
	philos = (t_philo *)malloc(sizeof(t_philo) * args.nbr_philo);
	if (!philos)
		return (4);
	if (!ft_init_tab(philos, &args))
		return (5);
	i = -1;
	while (++i < args.nbr_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher,
				(void *)&philos[i]))
			return (ft_free(philos, 6));
	}
	return (ft_end(&args, philos));
}

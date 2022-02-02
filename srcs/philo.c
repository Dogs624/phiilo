/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:29:12 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/02 12:29:32 by jvander-         ###   ########.fr       */
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

static	t_philo	ft_init_philo(int id, t_args *args)
{
	t_philo	philo;

	philo.id = id;
	philo.last_time_eat = args->start;
	philo.nbr_eat = 0;
	philo.args = args;
	philo.fork_r = NULL;
	if (pthread_mutex_init(&philo.fork_l, NULL) == -1)
		philo.id = -1;
	return (philo);
}

void	*philosopher(void *philo_void)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_void;
	i = 0;
	if (philo->id % 2)
		ft_usleep(10);
	while (!philo->args->is_dead
		&& philo->args->nbr_eat < philo->args->nbr_philo)
	{
		ft_take_fork(philo);
		if (ft_actual_time() - philo->last_time_eat > philo->args->time_to_die)
		{
			ft_died(philo);
			return (NULL);
		}
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo			*philos;
	int				i;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error number of arguments\n", 27);
		return (1);
	}
	args = ft_init_args(argc, argv);
	if (args.nbr_philo < 1)
		return (6);
	printf("int = %ld\n", args.time_to_die);
	philos = (t_philo *)malloc(sizeof(t_philo) * args.nbr_philo);
	if (!philos)
		return (4);
	i = -1;
	while (++i < args.nbr_philo)
	{
		philos[i] = ft_init_philo(i, &args);
		if (philos[i].id == -1)
		{
			free(philos);
			return (5);
		}
	}
	i = -1;
	while (++i < args.nbr_philo)
	{
		if (i == args.nbr_philo - 1)
			philos[i].fork_r = &philos[0].fork_l;
		else
			philos[i].fork_r = &philos[i + 1].fork_l;
	}
	i = -1;
	while (++i < args.nbr_philo)
	{
		pthread_create(&philos[i].thread, NULL, philosopher,
			(void *)&philos[i]);
	}
	i = -1;
	while (++i < args.nbr_philo)
	{
		if (pthread_join(philos[i].thread, NULL) == -1)
			return (EXIT_FAILURE);
	}
	return (0);
}

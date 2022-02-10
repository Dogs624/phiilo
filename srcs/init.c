/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:34:07 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/10 11:43:52 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	ft_init_philo(int id, t_args *args)
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

int	ft_init_tab(t_philo *philos, t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nbr_philo)
	{
		philos[i] = ft_init_philo(i, args);
		if (philos[i].id == -1)
		{
			free(philos);
			return (0);
		}
	}
	i = -1;
	while (++i < args->nbr_philo)
	{
		if (i == args->nbr_philo - 1)
			philos[i].fork_r = &philos[0].fork_l;
		else
			philos[i].fork_r = &philos[i + 1].fork_l;
	}
	return (1);
}

int	ft_destroy(t_args *args, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < args->nbr_philo)
	{
		if (pthread_detach(philos[i].thread) == -1)
		{
			pthread_mutex_unlock(&args->mutex_dead);
			pthread_mutex_unlock(&args->mutex_eat);
			return (ft_free(philos, 8));
		}
		if (pthread_mutex_destroy(&philos[i].fork_l) == -1)
		{
			pthread_mutex_unlock(&args->mutex_dead);
			pthread_mutex_unlock(&args->mutex_eat);
			return (ft_free(philos, 9));
		}
	}
	pthread_mutex_unlock(&args->mutex_dead);
	pthread_mutex_unlock(&args->mutex_eat);
	return (ft_free(philos, 0));
}

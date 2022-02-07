/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:29:29 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/07 11:14:28 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(t_philo *philo)
{
	ft_write("is sleeping", philo);
	if (!philo->args->is_dead)
		ft_usleep(philo->args->time_to_sleep, *philo);
}

void	ft_think(t_philo *philo)
{
	ft_write("is thinking", philo);
}

void	ft_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_dead);
	if (!philo->args->is_dead)
	{
		pthread_mutex_lock(&philo->args->mutex_write);
		printf("%ld %d died\n", ft_actual_time() - philo->args->start,
			philo->id + 1);
		pthread_mutex_unlock(&philo->args->mutex_write);
		philo->args->is_dead = 1;
	}
	pthread_mutex_unlock(&philo->args->mutex_dead);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	ft_write("has taken a fork", philo);
	if (philo->args->nbr_philo == 1)
	{
		ft_usleep(philo->args->time_to_die, *philo);
		ft_died(philo);
	}
	pthread_mutex_lock(philo->fork_r);
	ft_write("has taken a fork", philo);
}

void	ft_eat(t_philo *philo)
{
	philo->last_time_eat = ft_actual_time();
	ft_write("is eating", philo);
	ft_usleep(philo->args->time_to_eat, *philo);
	philo->nbr_eat++;
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	if (philo->nbr_eat == philo->args->nbr_time_must_eat
		&& philo->args->nbr_time_must_eat != -1)
	{
		pthread_mutex_lock(&philo->args->mutex_eat);
		philo->args->nbr_eat++;
		pthread_mutex_unlock(&philo->args->mutex_eat);
	}
}

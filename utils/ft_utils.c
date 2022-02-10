/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:41:34 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/10 13:27:29 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_write(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_write);
	pthread_mutex_lock(&philo->args->mutex_dead);
	pthread_mutex_lock(&philo->args->mutex_eat);
	if (!philo->args->is_dead && philo->args->nbr_eat < philo->args->nbr_philo)
	{
		printf("%ld %d %s\n", ft_actual_time() - philo->args->start,
			philo->id + 1, str);
	}
	pthread_mutex_unlock(&philo->args->mutex_dead);
	pthread_mutex_unlock(&philo->args->mutex_write);
	pthread_mutex_unlock(&philo->args->mutex_eat);
}

long int	ft_actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms, t_philo *philo)
{
	long int	start_time;

	start_time = 0;
	start_time = ft_actual_time();
	pthread_mutex_lock(&philo->args->mutex_dead);
	while ((ft_actual_time() - start_time) < time_in_ms
		&& ft_actual_time() - philo->last_time_eat < philo->args->time_to_die
		&& !philo->args->is_dead)
	{
		pthread_mutex_unlock(&philo->args->mutex_dead);
		usleep(time_in_ms / 10);
		pthread_mutex_lock(&philo->args->mutex_dead);
	}
	pthread_mutex_unlock(&philo->args->mutex_dead);
}

int	ft_check_time(t_philo *philo)
{
	if ((philo->args->time_to_eat - philo->args->time_to_sleep >= 50
			|| philo->args->time_to_eat - philo->args->time_to_sleep <= -50))
		return (1);
	return (0);
}

int	ft_free(t_philo *philos, int i)
{
	if (philos)
		free(philos);
	return (i);
}

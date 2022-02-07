/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:41:34 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/07 11:13:10 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_write(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_write);
	if (!philo->args->is_dead && philo->args->nbr_eat < philo->args->nbr_philo)
	{
		printf("%ld %d %s\n", ft_actual_time() - philo->args->start,
			philo->id + 1, str);
	}
	pthread_mutex_unlock(&philo->args->mutex_write);
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

void	ft_usleep(long int time_in_ms, t_philo philo)
{
	long int	start_time;

	start_time = 0;
	start_time = ft_actual_time();
	while ((ft_actual_time() - start_time) < time_in_ms && !philo.args->is_dead)
		usleep(time_in_ms / 100);
}
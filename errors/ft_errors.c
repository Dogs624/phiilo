/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:36:34 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/10 11:50:49 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_check_digits(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_check_digit(argv[i]))
		{
			write(2, "Error invalid arguments\n", 25);
			return (0);
		}
	}
	return (1);
}

int	ft_error(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		write(2, "Error number of arguments\n", 27);
		return (1);
	}
	if (ft_check_args_negative(argv))
	{
		write(2, "Error negative numbers\n", 24);
		return (1);
	}
	if (!ft_check_digits(argc, argv))
		return (1);
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			write(2, "Error invalid arguments\n", 25);
			return (1);
		}
	}
	return (0);
}

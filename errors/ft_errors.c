/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:36:34 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/07 10:42:35 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(int argc, char **argv)
{
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
	return (0);
}

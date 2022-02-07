/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:41:57 by jvander-          #+#    #+#             */
/*   Updated: 2022/02/07 10:42:31 by jvander-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_check_negative(char *nbr)
{
	if (!nbr)
		return (1);
	if (nbr[0] == '-')
		return (1);
	return (0);
}

int	ft_check_args_negative(char **nbrs)
{
	int	i;

	i = -1;
	while (nbrs[++i])
	{
		if (ft_check_negative(nbrs[i]))
			return (1);
	}
	return (0);
}
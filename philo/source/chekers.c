/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chekers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:40:08 by jnappa            #+#    #+#             */
/*   Updated: 2021/11/30 20:11:48 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	cheker_status(t_philo *next)
{
	t_philo	*begin;

	begin = next;
	if (begin->status == 0)
		return (1);
	begin = begin->next;
	while (begin != next)
	{
		if (begin->status == 0)
			return (1);
		begin = begin->next;
	}
	return (0);
}

int	cheker_numb_eating(t_data *all)
{
	int			number_eat;
	int			i;
	t_philo		*next;

	i = 0;
	number_eat = all->number_philo;
	next = all->philo;
	while (i < all->number_philo)
	{
		if (next->number_of_eating >= all->number_of_eating)
			number_eat--;
		next = next->next;
		i++;
	}
	if (number_eat == 0)
		return (1);
	return (0);
}

void	*cheker_of_dead(void *data)
{
	t_data			*all;
	t_philo			*next;
	struct timeval	tv;

	all = (t_data *)data;
	next = all->philo;
	while (next)
	{
		gettimeofday(&tv, NULL);
		if (next->time_to_dead < tv.tv_sec * 1000 + tv.tv_usec / 1000)
		{
			next->status = 0;
			printf("%ld %d died %ld\n", tv.tv_sec * 1000 + tv.tv_usec
				/ 1000, next->id + 1, next->time_to_dead);
			return (0);
		}
		if (all->number_of_eating >= 0 && cheker_numb_eating(all))
		{
			next->status = 0;
			return (0);
		}
		next = next->next;
	}
	return (0);
}

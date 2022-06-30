/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:54:20 by jnappa            #+#    #+#             */
/*   Updated: 2021/11/29 16:59:27 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_atoi(char *str)
{
	unsigned int	i;
	int				number;

	number = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (number);
}

int	first_information(char **argv, int argc, t_data *all)
{
	all->number_philo = ft_atoi(argv[1]);
	all->time_to_dead = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		all->number_of_eating = ft_atoi(argv[5]);
		if (all->number_of_eating == -1 || all->number_philo == -1
			|| all->time_to_dead == -1 || all->time_to_eat == -1
			|| all->time_to_sleep == -1)
			return (-1);
	}
	else
	{
		all->number_of_eating = -1;
		if (all->number_philo == -1 || all->time_to_dead == -1
			|| all->time_to_eat == -1 || all->time_to_sleep == -1)
			return (-1);
	}
	return (1);
}

static t_philo	*create_elem(int id, t_data *all)
{
	t_philo			*new;
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->back = NULL;
	new->id = id;
	new->status = 1;
	new->time_to_dead = tv.tv_sec * 1000 + tv.tv_usec
		/ 1000 + all->time_to_dead;
	new->time_to_eat = all->time_to_eat;
	new->time_to_sleep = all->time_to_sleep;
	new->time_to_meditate = all->time_to_meditate;
	new->time_dead = all->time_to_dead;
	new->number_of_eating = 0;
	return (new);
}

t_philo	*create_list(t_data *all)
{
	int		i;
	t_philo	*begin;
	t_philo	*next;

	i = 0;
	begin = NULL;
	while (i < all->number_philo)
	{
		if (begin == NULL)
		{
			begin = create_elem(i++, all);
			if (begin == NULL)
				return (NULL);
			next = begin;
			continue ;
		}
		next->next = create_elem(i, all);
		if (!next->next)
			return (free_list_philo(begin, i));
		next = next->next;
		i++;
	}
	next->next = begin;
	return (begin);
}

void	second_bundle(t_data *all)
{
	t_philo	*next;
	t_philo	*back;
	int		i;

	i = 0;
	next = all->philo;
	while (i < all->number_philo)
	{
		back = next;
		next = next->next;
		next->back = back;
		i++;
	}
}

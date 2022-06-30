/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:59:29 by jnappa            #+#    #+#             */
/*   Updated: 2021/11/30 20:55:41 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_potok(void *data)
{
	t_philo	*all;

	all = (t_philo *)data;
	pthread_detach(all->t);
	while (all->status != 0)
	{
		if (all->next == all)
			all->status = 0;
		eating(all);
		sleep_time(all);
		thinking_time(all);
	}
	return (0);
}

int	mutex_init(t_data *all)
{
	int	i;

	i = 0;
	while (i < all->number_philo)
	{
		if (pthread_mutex_init(&all->philo->mutex, NULL))
		{
			free_list_philo(all->philo, all->number_philo);
			return (0);
		}
		all->philo = all->philo->next;
		i++;
	}
	if (pthread_create(&all->t, NULL, cheker_of_dead, (void *)all))
	{
		free_list_philo(all->philo, all->number_philo);
		return (0);
	}
	return (1);
}

int	create_stream(t_data *all)
{
	int	i;

	i = 0;
	while (i < all->number_philo)
	{
		if (i % 2 == 0)
			if (pthread_create(&all->philo->t, NULL, philo_potok,
					(void *) all->philo))
				return (0);
		all->philo = all->philo->next;
		i++;
	}
	usleep(100);
	i = 0;
	while (i < all->number_philo)
	{
		if (i % 2 == 1)
			if (pthread_create(&all->philo->t, NULL, philo_potok,
					(void *)all->philo))
				return (0);
		all->philo = all->philo->next;
		i++;
	}
	return (1);
}

int	join_pthread(t_data *all)
{
	int	i;

	i = 0;
	pthread_join(all->t, NULL);
	while (i < all->number_philo)
	{
		pthread_join(all->philo->t, NULL);
		pthread_mutex_destroy(&all->philo->mutex);
		all->philo = all->philo->next;
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			all;

	if (argc < 5 || argc > 6)
	{
		printf("incorrect number of arguments\n");
		return (0);
	}
	if (first_information(argv, argc, &all) == -1)
	{
		printf("error in arguments\n");
		return (0);
	}
	all.philo = create_list(&all);
	second_bundle(&all);
	if (mutex_init(&all) == 0)
		return (0);
	if (create_stream(&all) == 0)
		return (0);
	join_pthread(&all);
	free_list_philo(all.philo, all.number_philo);
}

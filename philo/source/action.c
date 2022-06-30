/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:59:44 by jnappa            #+#    #+#             */
/*   Updated: 2021/11/30 20:42:58 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eating(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(&philo->next->mutex);
	pthread_mutex_lock(&philo->mutex);
	gettimeofday(&tv, NULL);
	if (cheker_status(philo))
		return ;
	printf("%ld %d has taken a fork\n",
		tv.tv_sec * 1000 + tv.tv_usec / 1000, philo->id + 1);
	usleep(philo->time_to_eat * 1000 - philo->time_to_eat * 20);
	philo->time_to_dead = tv.tv_sec * 1000 + tv.tv_usec / 1000
		+ philo->time_to_eat + philo->time_dead;
	if (cheker_status(philo))
		return ;
	printf("%ld %d is eating %ld\n",
		tv.tv_sec * 1000 + tv.tv_usec / 1000 + philo->time_to_eat,
		philo->id + 1, philo->time_to_dead);
	pthread_mutex_unlock(&philo->next->mutex);
	pthread_mutex_unlock(&philo->mutex);
	philo->number_of_eating++;
}

void	sleep_time(t_philo *philo)
{
	struct timeval	tv;

	usleep(philo->time_to_sleep * 1000);
	gettimeofday(&tv, NULL);
	if (cheker_status(philo))
		return ;
	printf("%ld %d is sleeping\n", tv.tv_sec * 1000 + tv.tv_usec / 1000,
		philo->id + 1);
}

void	thinking_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (cheker_status(philo))
		return ;
	printf("%ld %d is thinking\n", tv.tv_sec * 1000 + tv.tv_usec / 1000,
		philo->id + 1);
}

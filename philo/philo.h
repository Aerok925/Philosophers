/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:54:51 by jnappa            #+#    #+#             */
/*   Updated: 2021/11/30 20:34:11 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_meditate;
	int				time_dead;
	int				status;
	long int		time_to_dead;
	int				number_of_eating;
	unsigned int	id;
	struct s_philo	*next;
	struct s_philo	*back;
	pthread_mutex_t	mutex;
	pthread_mutex_t	me;
	pthread_t		t;
}	t_philo;

typedef struct s_data
{
	int				number_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_dead;
	int				time_to_meditate;
	int				number_of_eating;
	pthread_t		t;
	t_philo			*philo;
}	t_data;

void	eating(t_philo *philo);
void	sleep_time(t_philo *philo);
void	thinking_time(t_philo *philo);
void	*cheker_of_dead(void *data);
int		cheker_status(t_philo *next);
void	second_bundle(t_data *all);
t_philo	*create_list(t_data *all);
t_philo	*free_list_philo(t_philo *begin, int max);
int		first_information(char **argv, int argc, t_data *all);

#endif //PHILO_H

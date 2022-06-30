/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnappa <jnappa@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:59:54 by jnappa            #+#    #+#             */
/*   Updated: 2021/11/29 17:00:06 by jnappa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*free_list_philo(t_philo *begin, int max)
{
	t_philo	*next;
	int		i;

	i = 0;
	while (i < max)
	{
		next = begin->next;
		free(begin);
		begin = NULL;
		begin = next;
		i++;
	}
	return (NULL);
}

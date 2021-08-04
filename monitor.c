/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrace <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 09:31:16 by sthrace           #+#    #+#             */
/*   Updated: 2021/08/04 09:31:18 by sthrace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	food_counter(t_philo *ph)
{
	if (ph->data->status == ALIVE)
	{
		pthread_mutex_lock(&ph->data->m_food);
		ph->num_meals++;
		pthread_mutex_unlock(&ph->data->m_food);
		pthread_mutex_lock(&ph->data->m_food);
		if (ph->num_meals == ph->data->meals)
			ph->data->full++;
		pthread_mutex_unlock(&ph->data->m_food);
		if (ph->data->full == ph->data->cnt)
		{
			pthread_mutex_lock(&ph->data->m_status);
			ph->data->status = FULL;
			printf("All philosophers ate %d times\n", ph->data->meals);
			return ;
		}
	}
}

void	*deathcycle(void *arg)
{
	t_philo			*ph;
	uint64_t		now;
	uint64_t		diff;

	ph = (t_philo *)arg;
	while (ph->data->status == ALIVE)
	{
		pthread_mutex_lock(&ph->data->m_death);
		now = ft_gettime();
		diff = now - ph->last_meal;
		pthread_mutex_unlock(&ph->data->m_death);
		if (diff > (uint64_t)ph->data->t2d)
		{
			pthread_mutex_lock(&ph->data->m_status);
			ft_print(ph, "died");
			ph->data->status = DEAD;
			break ;
		}
		ft_usleep(9);
	}
	return (NULL);
}

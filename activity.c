/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrace <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 09:31:25 by sthrace           #+#    #+#             */
/*   Updated: 2021/08/04 09:31:27 by sthrace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_locked(t_philo *ph, int type)
{
	if (type == 1)
	{
		if (pthread_mutex_lock(&ph->lfork))
		{
			pthread_mutex_unlock(ph->rfork);
			ft_eat(ph);
		}
	}
	if (type == 2)
	{
		if (pthread_mutex_lock(ph->rfork))
		{
			pthread_mutex_unlock(&ph->lfork);
			ft_eat(ph);
		}
	}
}

void	ft_eat(t_philo *ph)
{
	if (!(ph->id % 2))
		pthread_mutex_lock(ph->rfork);
	else
		pthread_mutex_lock(&ph->lfork);
	ft_print(ph, "has taken a fork");
	if (ph->data->cnt == 1)
	{
		pthread_mutex_unlock(ph->rfork);
		return ;
	}
	if (!(ph->id % 2))
		ft_locked(ph, 1);
	else
		ft_locked(ph, 2);
	ft_print(ph, "has taken a fork");
	pthread_mutex_lock(&ph->data->m_food);
	ph->last_meal = ft_gettime();
	pthread_mutex_unlock(&ph->data->m_food);
	ft_print(ph, "is eating");
	ft_usleep(ph->data->t2e);
	food_counter(ph);
	pthread_mutex_unlock(ph->rfork);
	pthread_mutex_unlock(&ph->lfork);
}

void	*lifecycle(void *arg)
{
	t_philo		*ph;
	pthread_t	t_death;

	ph = (t_philo *)arg;
	if (pthread_create(&t_death, NULL, &deathcycle, ph))
	{
		printf("Pthread create failed\n");
		return (NULL);
	}
	if (pthread_detach(t_death))
	{
		printf("Pthread detach failed\n");
		return (NULL);
	}
	while (ph->data->status == ALIVE)
	{
		ft_eat(ph);
		ft_print(ph, "is sleeping");
		ft_usleep(ph->data->t2s);
		ft_print(ph, "is thinking");
	}
	return (NULL);
}

static int	create_threads(t_philo *ph, int i)
{
	if (pthread_create(&ph[i].t_ph, NULL, &lifecycle, &ph[i]))
	{
		printf("Pthread create failed\n");
		return (1);
	}
	ft_usleep(1 / 10);
	return (0);
}

int	thread_init(t_philo *ph, int i)
{
	while (i < ph->data->cnt)
	{
		if (create_threads(ph, i))
			return (1);
		i += 2;
	}
	ft_usleep(ph->data->t2e / ph->data->cnt);
	i = 1;
	while (i < ph->data->cnt)
	{
		if (create_threads(ph, i))
			return (1);
		i += 2;
	}
	i = -1;
	while (++i < ph->data->cnt)
	{
		if (pthread_join(ph[i].t_ph, NULL))
		{
			printf("Pthread detach failed\n");
			return (1);
		}
	}
	mutex_destroy(ph);
	return (0);
}

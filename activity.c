#include "philo.h"

static void	ft_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->lfork);
	ft_print(ph, "has taken a fork");
	if (ph->data->cnt == 1)
	{
		pthread_mutex_unlock(&ph->lfork);
		return ;
	}
	pthread_mutex_lock(ph->rfork);
	ft_print(ph, "has taken a fork");
	pthread_mutex_lock(&ph->data->m_food);
	ph->last_meal = ft_gettime();
	pthread_mutex_unlock(&ph->data->m_food);
	ft_print(ph, "is eating");
	ft_usleep(ph->data->t2e);
	pthread_mutex_lock(&ph->data->m_food);
	if (ph->data->status == ALIVE)
		food_counter(ph);
	pthread_mutex_unlock(&ph->data->m_food);
	pthread_mutex_unlock(ph->rfork);
	pthread_mutex_unlock(&ph->lfork);
}

void	*lifecycle(void *arg)
{
	t_philo	*ph;
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

int	thread_init(t_philo *ph, int i)
{
	while (ph->data->status == ALIVE)
	{
		i = 0;
		while (i < ph->data->cnt)
		{
			if (pthread_create(&ph[i].t_ph, NULL, &lifecycle, &ph[i]))
			{
				printf("Pthread create failed\n");
				return (1);
			}
			i = i + 2;
		}
		ft_usleep(ph->data->t2e / 2);
		i = 1;
		while (i < ph->data->cnt)
		{
			if (pthread_create(&ph[i].t_ph, NULL, &lifecycle, &ph[i]))
			{
				printf("Pthread create failed\n");
				return (1);
			}
			i = i + 2;
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
	}
	pthread_mutex_destroy(&ph->data->m_death);
	pthread_mutex_destroy(&ph->data->m_food);
	pthread_mutex_destroy(&ph->data->m_print);
	return (0);
}
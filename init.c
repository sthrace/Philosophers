#include "philo.h"

static int	thread_init(t_philo *ph, int i)
{
	i = -1;
	while (++i < ph->data->cnt)
	{
		if (pthread_create(&ph[i].t_ph, NULL, &lifecycle, &ph[i]))
		{
			printf("Pthread create failed\n");
			return (1);
		}
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
	pthread_mutex_destroy(&ph->mutex->m_death);
	pthread_mutex_destroy(&ph->mutex->m_food);
	pthread_mutex_destroy(&ph->mutex->m_print);
	return (0);
}

int	simulation_init(t_philo *ph, t_data *data, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < data->cnt)
	{
		ph[i].id = i + 1;
		ph[i].data = data;
		ph[i].mutex = mutex;
		ph[i].last_meal = data->start;
		ph[i].num_meals = 0;
		if (pthread_mutex_init(&ph[i].lfork, NULL))
		{
			printf("Fork mutex init failed\n");
			return (1);
		}
		if (i == data->cnt - 1)
			ph[i].rfork = &ph[0].lfork;
		else
			ph[i].rfork = &ph[i + 1].lfork;
		i++;
	}
	if (thread_init(ph, -1))
		return (1);
	return (0);
}
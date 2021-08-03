#include "philo.h"

static int	thread_init(t_philo *ph, int i)
{
	while (ph->data->status == ALIVE)
	{
		// if (pthread_create(&ph->data->t_death, NULL, &deathcycle, (void *)ph))
		// {
		// 	printf("Pthread create failed\n");
		// 	return (1);
		// }
		i = -1;
		while (++i < ph->data->cnt)
		{
			if (pthread_create(&ph[i].t_ph, NULL, &lifecycle, &ph[i]))
			{
				printf("Pthread create failed\n");
				return (1);
			}
			ft_usleep(1);
		}
		i = -1;
		while (++i < ph->data->cnt)
		{
			if (pthread_detach(ph[i].t_ph))
			{
				printf("Pthread detach failed\n");
				return (1);
			}
		}
		// if (pthread_detach(ph->data->t_death))
		// {
		// 	printf("Pthread detach failed\n");
		// 	return (1);
		// }
	}
	pthread_mutex_destroy(&ph->data->m_death);
	pthread_mutex_destroy(&ph->data->m_food);
	pthread_mutex_destroy(&ph->data->m_print);
	return (0);
}


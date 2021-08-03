#include "philo.h"

void	food_counter(t_philo *ph)
{
	ph->num_meals++;
	if (ph->num_meals == ph->data->meals)
		ph->data->full++;
	if (ph->data->full == ph->data->cnt)
	{
		// pthread_mutex_lock(&ph->data->m_death);
		ph->data->status = FULL;
		printf("All philosophers ate %d times\n", ph->data->meals);
		return ;
	}
}

void	*deathcycle(void *arg)
{
	t_philo			*ph;
	uint64_t		now;
	uint64_t		diff;

	ph = (t_philo *)arg;
	while (ph->data->status ==ALIVE)
	{
		pthread_mutex_lock(&ph->data->m_death);
		now = ft_gettime();
		diff = now - ph->last_meal;
		pthread_mutex_unlock(&ph->data->m_death);
		if (diff > (uint64_t)ph->data->t2d)
		{
			ft_print(ph, "died");
			ph->data->status = DEAD;
			return (NULL);
		}
	}
	return (NULL);
}
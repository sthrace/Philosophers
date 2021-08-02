#include "philo.h"

void	food_counter(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex->m_food);
	ph->last_meal = ft_gettime();
	ph->num_meals++;
	if (ph->num_meals == ph->data->meals)
		ph->data->full++;
	if (ph->data->full == ph->data->cnt)
	{
		ph->data->status = FULL;
		printf("All philosophers ate %d times\n", ph->data->meals);
	}
	pthread_mutex_unlock(&ph->mutex->m_food);
}

void	checkdeath(t_philo *ph)
{
	uint64_t	now;
	uint64_t	diff;

	pthread_mutex_lock(&ph->mutex->m_death);
	now = ft_gettime();
	diff = now - ph->last_meal;
	printf("Diff for %d is %lu\n", ph->id, diff);
	if (diff > (uint64_t)ph->data->t2d)
	{
		ph->data->status = DEAD;
		ft_print(ph, "died");
	}
	pthread_mutex_unlock(&ph->mutex->m_death);
}
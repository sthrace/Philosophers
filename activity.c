#include "philo.h"

static void	ft_sleep(t_philo *ph)
{
	if (ph->data->status != ALIVE)
		return ;
	pthread_mutex_lock(&ph->mutex->m_print);
	if (ph->data->status == ALIVE)
		ft_print(ph, "is sleeping");
	pthread_mutex_unlock(&ph->mutex->m_print);
	ft_usleep(ph->data->t2s);
	if (ph->data->status != ALIVE)
		return ;
	pthread_mutex_lock(&ph->mutex->m_print);
	if (ph->data->status == ALIVE)
		ft_print(ph, "is thinking");
	pthread_mutex_unlock(&ph->mutex->m_print);
}

static void	ft_eat_r(t_philo *ph)
{
	if (ph->data->status != ALIVE)
		return ;
	pthread_mutex_lock(ph->rfork);
	pthread_mutex_lock(&ph->mutex->m_print);
	if (ph->data->status == ALIVE)
		ft_print(ph, "has taken a fork");
	pthread_mutex_unlock(&ph->mutex->m_print);
	pthread_mutex_lock(&ph->lfork);
	pthread_mutex_lock(&ph->mutex->m_print);
	if (ph->data->status == ALIVE)
		checkdeath(ph);			// taking up 200 ms time && too few deathchecks. must print death not later than 10 ms after philo dies
	if (ph->data->status == ALIVE)
	{
		ft_print(ph, "has taken a fork");
		ft_print(ph, "is eating");
	}
	pthread_mutex_unlock(&ph->mutex->m_print);
	if (ph->data->status == ALIVE)
		food_counter(ph);
	if (ph->data->status != ALIVE)
		return ;
	ft_usleep(ph->data->t2e);
	pthread_mutex_unlock(&ph->lfork);
	pthread_mutex_unlock(ph->rfork);
}

static void	ft_eat_l(t_philo *ph)
{
	if (ph->data->status != ALIVE)
		return ;
	pthread_mutex_lock(&ph->lfork);
	pthread_mutex_lock(&ph->mutex->m_print);
	if (ph->data->status == ALIVE)
		ft_print(ph, "has taken a fork");
	pthread_mutex_unlock(&ph->mutex->m_print);
	pthread_mutex_lock(ph->rfork);
	pthread_mutex_lock(&ph->mutex->m_print);
	if (ph->data->status == ALIVE)
		checkdeath(ph);		// taking up 200 ms time && too few deathchecks. must print death not later than 10 ms after philo dies
	if (ph->data->status == ALIVE)
	{
		ft_print(ph, "has taken a fork");
		ft_print(ph, "is eating");
	}
	pthread_mutex_unlock(&ph->mutex->m_print);
	if (ph->data->status == ALIVE)
		food_counter(ph);
	if (ph->data->status != ALIVE)
		return ;
	ft_usleep(ph->data->t2e);
	pthread_mutex_unlock(&ph->lfork);
	pthread_mutex_unlock(ph->rfork);
}

void	*lifecycle(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (ph->data->status == ALIVE)
	{
		if (ph->data->status != ALIVE)
			return (NULL);
		if (ph->id % 2)
			ft_eat_l(ph);
		else
			ft_eat_r(ph);
		ft_sleep(ph);
	}
	return (NULL);
}
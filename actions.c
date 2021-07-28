#include "philo.h"

void	ft_check_death(t_philo *ph)
{
	uint64_t	time;

	// pthread_mutex_lock(&ph->data->death);
	time = ft_get_time();
	printf("Time for %d: %lu\n", ph->number, time);
	printf("Start for %d: %lu\n", ph->number, ph->start_meal);
	printf("Diff for %d: %lu\n", ph->number, time - ph->start_meal);
	if ((time - ph->start_meal) > (uint64_t)ph->data->die * 1000)
	{
		pthread_mutex_lock(&ph->data->print);
		ph->data->is_alive = 0;
		ft_printer(ph, "died");
		ft_exit(10);
	}
	// pthread_mutex_unlock(&ph->data->death);
}

void	ft_eat(t_philo *ph)
{
	if (!(ph->number % 2))
		pthread_mutex_lock(ph->rfork);
	else
		pthread_mutex_lock(&ph->lfork);
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "has taken a fork");
	pthread_mutex_unlock(&ph->data->print);
	if (!(ph->number % 2))
	{
		pthread_mutex_unlock(ph->rfork);
		return ;
	}
	else if (ph->number % 2 && !ph->rfork)
	{
		pthread_mutex_unlock(&ph->lfork);
		return ;
	}
	if (!(ph->number % 2))
		pthread_mutex_lock(&ph->lfork);
	else
		pthread_mutex_lock(ph->rfork);
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "has taken a fork");
	ph->start_meal = ft_get_time();
	ft_printer(ph, "is eating");
	pthread_mutex_unlock(&ph->data->print);
	ft_usleep(ph->data->eat);
	pthread_mutex_unlock(ph->rfork);
	pthread_mutex_unlock(&ph->lfork);
}

void	ft_sleep(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "is sleeping");
	pthread_mutex_unlock(&ph->data->print);
	ft_usleep(ph->data->sleep);
}

void	ft_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "is thinking");
	pthread_mutex_unlock(&ph->data->print);
}

void	*lifecycle(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (ph->data->is_alive)
	{
		if (ph->data->satisfied == ph->data->philo_cnt)
		{
			pthread_mutex_lock(&ph->data->print);
			ft_exit(9);
		}
		pthread_mutex_lock(&ph->data->death);
		ft_check_death(ph);
		pthread_mutex_unlock(&ph->data->death);
		ft_eat(ph);
		if (ph->data->eat_cnt != -1)
			ft_meal_counter(ph);
		pthread_mutex_lock(&ph->data->death);
		ft_check_death(ph);
		pthread_mutex_unlock(&ph->data->death);
		ft_sleep(ph);
		pthread_mutex_lock(&ph->data->death);
		ft_check_death(ph);
		pthread_mutex_unlock(&ph->data->death);
		ft_think(ph);
	}
	return (NULL);
}
#include "philo.h"

void	*death_check(void *arg)
{
	uint64_t	time;
	t_all	*all;
	int		i;

	all = (t_all *)arg;

	time = ft_get_time();
	while (1)
	{
		i = 0;
		while (i < all->data.philo_cnt)
		{
			if ((time - all->philo[i].start_meal) > (uint64_t)all->data.die)
			{
				all->data.is_alive = 0;
				pthread_mutex_lock(&all->data.print);
				ft_printer(all->philo, "died");
				ft_exit(10);
			}
			i++;
		}
	}
	return (NULL);
}

void	ft_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->lfork);
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "has taken a fork");
	pthread_mutex_unlock(&ph->data->print);
	if (!ph->rfork)
	{
		pthread_mutex_unlock(&ph->lfork);
		return ;
	}
	pthread_mutex_lock(ph->rfork);
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "has taken a fork");
	ph->start_meal = ft_get_time();
	ft_printer(ph, "is eating");
	pthread_mutex_unlock(&ph->data->print);
	ft_usleep(ph->data->eat / 1000);
	pthread_mutex_unlock(ph->rfork);
	pthread_mutex_unlock(&ph->lfork);
}

void	ft_sleep(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "is sleeping");
	pthread_mutex_unlock(&ph->data->print);
	ft_usleep(ph->data->sleep / 1000);
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
		ft_eat(ph);
		if (ph->data->eat_cnt != -1)
			ft_meal_counter(ph);
		ft_sleep(ph);
		ft_think(ph);
	}
	return (NULL);
}
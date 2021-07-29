#include "philo.h"

void	ft_got_food(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->food);
	ph->got_food++;
	pthread_mutex_unlock(&ph->data->food);
	if (ph->got_food == ph->data->eat_cnt)
	{
		pthread_mutex_lock(&ph->data->food);
		ph->data->satisfied++;
		pthread_mutex_unlock(&ph->data->food);
	}
}

void	*death_check(void *arg)
{
	t_philo	*ph;
	uint64_t	now;

	ph = (t_philo *)arg;
	pthread_mutex_lock(&ph->data->is_dead);
	now = ft_get_time() - ph->start_meal;
	// printf("Diff is: %lu\n", ft_get_time() - ph->start_meal);
	if (now >= (uint64_t)ph->data->die)
	{
		ph->data->all_alive = 0;
		pthread_mutex_lock(&ph->data->print);
		ft_printer(ph, "died");
		ft_exit(10);
	}
	pthread_mutex_unlock(&ph->data->is_dead);
	return (NULL);
}

void	ft_sleep(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "is sleeping");
	ft_usleep(ph->data->sleep);
	pthread_mutex_unlock(&ph->data->print);
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "is thinking");
	pthread_mutex_unlock(&ph->data->print);
}

void	ft_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->lfork);
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "has taken a fork");
	pthread_mutex_unlock(&ph->data->print);
	if (!ph->rfork || ph->data->philo_cnt == 1)
	{
		if (ph->data->philo_cnt == 1)
			ft_usleep(ph->data->die + 1);
		return ;
	}
	pthread_mutex_lock(ph->rfork);
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "has taken a fork");
	ph->start_meal = ft_get_time();
	ft_printer(ph, "is eating");
	pthread_mutex_unlock(&ph->data->print);
	ft_usleep(ph->data->eat);
	ft_got_food(ph);
	pthread_mutex_unlock(ph->rfork);
	pthread_mutex_unlock(&ph->lfork);
}

void	*lifecycle(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		if (pthread_create(&ph->data->death, NULL, &death_check, ph))
			ft_exit(7);
		ft_eat(ph);
		if (ph->data->satisfied == ph->data->philo_cnt)
		{
			pthread_mutex_lock(&ph->data->print);
			printf("All philosophers ate\n");
			pthread_mutex_unlock(&ph->data->food);
			ft_exit(10);
		}
		ft_sleep(ph);
		if (pthread_detach(ph->data->death))
			ft_exit(8);
	}
	return (NULL);
}
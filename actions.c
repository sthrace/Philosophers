#include "philo.h"

void	ft_check_death(t_philo *ph)
{
	uint64_t	time;

	time = ft_get_time();
	if ((time - ph->start_meal) > (uint64_t)ph->data->die)
	{
		ph->data->death = 1;
		pthread_mutex_lock(&ph->data->print);
		ft_printer(ph, "died");
		pthread_mutex_unlock(&ph->data->print);
		ft_exit(10);
	}
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
	ft_check_death(ph);
	ph->start_meal = ft_get_time();
	ft_printer(ph, "is eating");
	pthread_mutex_unlock(&ph->data->print);
	ft_usleep(ph->data->eat / 1000);
	pthread_mutex_unlock(ph->rfork);
	pthread_mutex_unlock(&ph->lfork);
	ft_check_death(ph);
}

void	ft_sleep(t_philo *ph)
{
	ft_check_death(ph);
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "is sleeping");
	pthread_mutex_unlock(&ph->data->print);
	ft_usleep(ph->data->sleep / 1000);
	ft_check_death(ph);
}

void	ft_think(t_philo *ph)
{
	ft_check_death(ph);
	pthread_mutex_lock(&ph->data->print);
	ft_printer(ph, "is thinking");
	pthread_mutex_unlock(&ph->data->print);
	ft_check_death(ph);
}

void	*lifecycle(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
	// 	if (ph->data->satisfied == ph->data->philo_cnt)
	// 	{
	// 		pthread_mutex_lock(&ph->data->print);
	// 		ft_exit(9);
	// 	}
	// 	printf("Will now eat\n");
		ft_eat(ph);
	// 	if (ph->data->eat_cnt != -1)
	// 		ft_meal_counter(ph);
		ft_sleep(ph);
		ft_think(ph);
	}
	// return (NULL);
	// t_philo	*ph;

	// ph = (t_philo *)arg;
	// ph->got_food = 7;
	// printf("ph number %d Got food\n", ph->number);
	return (NULL);
}
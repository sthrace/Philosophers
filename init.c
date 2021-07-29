#include "philo.h"

void	ft_pthread_start(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data.philo_cnt)
	{
		if (!(i % 2))
		{
			if (pthread_create(&all->philo[i].thread, NULL, &lifecycle, &all->philo[i]))
				ft_exit(7);
			all->philo[i].start_meal = ft_get_time();
			// if (pthread_join(all->philo[i].thread, NULL))
			// 	ft_exit(8);
			// usleep(all->data.sleep / all->data.philo_cnt);
		}
		i++;
	}
	i = 0;
	usleep(all->data.die / all->data.philo_cnt);
	while (i < all->data.philo_cnt)
	{
		if (i % 2)
		{
			if (pthread_create(&all->philo[i].thread, NULL, &lifecycle, &all->philo[i]))
				ft_exit(7);
			all->philo[i].start_meal = ft_get_time();
			// if (pthread_join(all->philo[i].thread, NULL))
			// 	ft_exit(8);
			// usleep(all->data.sleep / all->data.philo_cnt);
		}
		i++;
	}
	i = 0;
	while (i < all->data.philo_cnt)
	{
		if (pthread_join(all->philo[i].thread, NULL))
			ft_exit(8);
		usleep(all->data.sleep / all->data.philo_cnt);
		i++;
	}
	i = 0;
	while (i < all->data.philo_cnt)
	{
		pthread_mutex_destroy(&all->philo[i].lfork);
		i++;
	}
	pthread_mutex_destroy(&all->data.is_dead);
	pthread_mutex_destroy(&all->data.food);
}

void	ft_pthread_init(t_all *all)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&all->data.is_dead, NULL))
		ft_exit(6);
	if (pthread_mutex_init(&all->data.food, NULL))
		ft_exit(6);
	while (i < all->data.philo_cnt)
	{
		all->philo[i].data = &all->data;
		all->philo[i].number = i + 1;
		all->philo[i].got_food = 0;
		if (all->data.philo_cnt == 1)
		{
			all->philo[0].rfork = NULL;
			if (pthread_mutex_init(&all->philo[0].lfork, NULL))
				ft_exit(6);
		}
		if (pthread_mutex_init(&all->philo[i].lfork, NULL))
				ft_exit(6);
		if (i == all->data.philo_cnt - 1)
			all->philo[i].rfork = &all->philo[0].lfork;
		else
			all->philo[i].rfork = &all->philo[i + 1].lfork;
		i++;
	}
}
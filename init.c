#include "philo.h"

void	ft_mdestroy(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data.philo_cnt)
	{
		pthread_mutex_destroy(&all->philo[i].lfork);
		i++;
	}
}

void	ft_join(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data.philo_cnt)
	{
		if (pthread_join(all->philo[i].thread, NULL))
			ft_exit(8);
		i++;
	}
	if (pthread_join(all->data.death, NULL))
			ft_exit(8);
	ft_mdestroy(all);
}

void	ft_pthread_start(t_all *all,  int i)
{
	pthread_mutex_init(&all->data.print, NULL);
	if (pthread_create(&all->data.death, NULL, &death_check, &all))
				ft_exit(6);
	while (++i < all->data.philo_cnt)
	{
		if (i % 2)
		{
			all->philo[i].start_meal = ft_get_time();
			if (pthread_create(&all->philo[i].thread, NULL, &lifecycle, &all->philo[i]))
				ft_exit(6);
		}
	}
	i = -1;
	while (++i < all->data.philo_cnt)
	{
		if (!(i % 2))
		{
			all->philo[i].start_meal = ft_get_time();
			if (pthread_create(&all->philo[i].thread, NULL, &lifecycle, &all->philo[i]))
				ft_exit(6);
		}
	}
	ft_join(all);
}

void	ft_pthread_init(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data.philo_cnt)
	{
		all->philo[i].data = &all->data;
		all->philo[i].number = i + 1;
		if (all->data.philo_cnt)
		{
			all->philo[0].rfork = NULL;
			if (pthread_mutex_init(&all->philo[0].lfork, NULL))
				ft_exit(7);
		}
		if (i == all->data.philo_cnt - 1)
			all->philo[i].rfork = &all->philo[0].lfork;
		else
			all->philo[i].rfork = &all->philo[i + 1].lfork;
		if (pthread_mutex_init(&all->philo[i].lfork, NULL))
				ft_exit(7);
		if (all->data.eat_cnt != -1)
			all->philo[i].got_food = 0;
		i++;
	}
	ft_pthread_start(all, -1);
}
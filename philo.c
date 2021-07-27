#include "philo.h"

uint64_t	ft_get_time()
{
	uint64_t			time;
	static struct timeval		timer;

	time = 0;
	if (gettimeofday(&timer, NULL) == -1)
		ft_exit(4);
	time = (timer.tv_sec * 1000) + (timer.tv_usec / 1000);
	return (time);
}

void	ft_printer(t_philo *philo, char *str)
{
	uint64_t	now;

	printf("OK\n");
	printf("Value: %lu\n", philo->data->start);
	now = ft_get_time() - philo->data->start;
	while (1)
	{
		sleep (2);
		printf("GETTIME: %lu\n", ft_get_time());
		printf("START: %lu\n", philo->data->start);
		printf("NOW: %lu\n", now);
	}
	printf("%lu %d is %s\n", now, philo->number, str);
}

void	*routine(void *arg)
{
	t_philo	*temp;

	temp = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(temp->rfork);
		pthread_mutex_lock(&temp->lfork);
		ft_printer(temp, "is eating");
		usleep(temp->data->eat);
		pthread_mutex_unlock(&temp->lfork);
		pthread_mutex_unlock(temp->rfork);
		ft_printer(temp, "is sleeping");
		usleep(temp->data->sleep);
		ft_printer(temp, "is thinking");
	}
}

void	ft_init_simulation(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data.philo_cnt)
	{
		all->philo[i].data = &all->data;
		all->philo[i].number = i + 1;
		if (i == all->data.philo_cnt)
			all->philo[i].rfork = &all->philo[0].lfork;
		else
			all->philo[i].rfork = &all->philo[i + 1].lfork;
		if (all->data.eat_cnt != 1)
			all->philo[i].ate = 0;
		if (pthread_create(&all->philo[i].thread, NULL, &routine, &all->philo[i]))		//create thread
			ft_exit(6);
		pthread_mutex_init(&all->philo[i].lfork, NULL);
		i++;
	}
	i = 0;
	while (i < all->data.philo_cnt)
	{
		if (pthread_join(all->philo[i].thread, NULL))
			ft_exit(7);
		i++;
	}
	i = 0;
	while (i < all->data.philo_cnt)
	{
		pthread_mutex_destroy(&all->philo[i].lfork);
		i++;
	}
}

void	ft_init_struct(t_all *all, int argc, char **argv)
{
	all->data.philo_cnt = ft_atoi_philo(argv[1], 1);
	all->data.die = ft_atoi_philo(argv[2], 2);
	all->data.eat = ft_atoi_philo(argv[3], 2);
	all->data.sleep = ft_atoi_philo(argv[4], 2);
	all->data.start = ft_get_time();
	printf("Start at: %lu\n", all->data.start);
	if (argc == 6)
		all->data.eat_cnt = ft_atoi_philo(argv[5], 2);
	else
		all->data.eat_cnt = -1;
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->data.philo_cnt);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc < 5 || argc > 6)
		ft_exit(3);
	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		ft_exit(5);
	ft_init_struct(all, argc, argv);
	ft_init_simulation(all);
	return (0);
}
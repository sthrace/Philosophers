#include "philo.h"

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine(t_data *data)
{
	// int		i;
	// i = 0;
	// while (i < 1000000)
	// {
	// 	pthread_mutex_lock(&mutex);
	// 	mails++;
	// 	pthread_mutex_unlock(&mutex);
	// 	i++;
	// }
	// return (NULL);
	while (1)
	{
		printf("Philo %d is thinking\n", data->philo->number);
		printf("Philo %d is eating\n", data->philo->number);
		usleep(data->eat);
		printf("Philo %d is sleeping\n", data->philo->number);
		usleep(data->sleep);
	}
}

int	ft_init_simulation(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);		// initialize mutex;
	while (i < data->philo_cnt)
	{
		data->philo->number = i + 1;
		if (pthread_create(&data->philo[i].thread, NULL, &routine(data), NULL))		//create thread
			return (1);
		printf("Thread %d started\n", i);
		i++;
	}
	i = 0;
	while (i < data->philo_cnt)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (1);
		printf("Thread %d finished\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);		//free memory allocated to mutex;
	printf("Number of mails: %d\n", mails);
	return (0);
}

void	ft_init_struct(t_data *data, int argc, char **argv)
{
	data->philo_cnt = ft_atoi_philo(argv[1], 1);
	data->die = ft_atoi_philo(argv[2], 2);
	data->eat = ft_atoi_philo(argv[3], 2);
	data->sleep = ft_atoi_philo(argv[4], 2);
	if (argc == 6)
		data->eat_cnt = ft_atoi_philo(argv[5], 2);
	else
		data->eat_cnt = -1;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_cnt);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		ft_exit(3);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_init_struct(data, argc, argv);
	if (ft_init_simulation(data))
		return (1);
	return (0);
}
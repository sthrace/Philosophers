#include "philo.h"

static int	ft_atoi_philo(char *arg)
{
	int	i;
	long	res;

	i = 0;
	res = 0;
	while (arg[i])
	{
		res = res * 10 + (arg[i] - 48);
		i++;
	}
	if (res > __INT_MAX__ || res < 1)
		return (0);
	return ((int)res);
}

static int	init_mutex(t_mutex *mutex)
{
	if (pthread_mutex_init(&mutex->m_print, NULL) \
	|| pthread_mutex_init(&mutex->m_death, NULL) \
	|| pthread_mutex_init(&mutex->m_food, NULL))
	{
		printf("Mutex init failed\n");
		return (1);
	}
	return (0);	
}

static int	init_data(t_data *data, int argc, char **argv)
{
	data->cnt = ft_atoi_philo(argv[1]);
	data->t2d = ft_atoi_philo(argv[2]);
	data->t2e = ft_atoi_philo(argv[3]);
	data->t2s = ft_atoi_philo(argv[4]);
	data->meals = 0;
	data->full = 0;
	data->start = ft_gettime();
	data->status = ALIVE;
	if (argc == 6)
		data->meals = ft_atoi_philo(argv[5]);
	if (!data->cnt || !data->t2d || !data->t2e || !data->t2s || (argc == 6 && !data->meals) || !data->start)
	{
		printf("Data initialization failed\n");
		return (1);
	}
	return (0);
}

static int	validate_argv(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Only integers passed to parameters are accepted\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*ph;
	t_data	data;
	t_mutex	mutex;

	if (argc < 5 || argc > 6)
	{
		printf("Number of arguments must be 4 or 5\n");
		return (1);
	}
	if (validate_argv(argv) || init_data(&data, argc, argv) || init_mutex(&mutex))
		return (1);
	ph = (t_philo *)malloc(sizeof(t_philo) * data.cnt);
	if (ph == NULL)
	{
		printf("Malloc for philo structure failed\n");
		return (1);
	}
	if (simulation_init(ph, &data, &mutex))
		return (1);
	return (0);
}
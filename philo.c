/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrace <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 09:31:08 by sthrace           #+#    #+#             */
/*   Updated: 2021/08/04 09:31:10 by sthrace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi_philo(char *arg)
{
	int		i;
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

static int	init_philo(t_philo *ph, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cnt)
	{
		ph[i].id = i + 1;
		ph[i].data = data;
		ph[i].last_meal = data->start;
		ph[i].num_meals = 0;
		if (pthread_mutex_init(&ph[i].lfork, NULL))
		{
			printf("Fork mutex init failed\n");
			return (1);
		}
		if (i == data->cnt - 1)
			ph[i].rfork = &ph[0].lfork;
		else
			ph[i].rfork = &ph[i + 1].lfork;
		i++;
	}
	if (thread_init(ph, 0))
		return (1);
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
	if (pthread_mutex_init(&data->m_print, NULL) \
	|| pthread_mutex_init(&data->m_death, NULL) \
	|| pthread_mutex_init(&data->m_food, NULL) \
	|| pthread_mutex_init(&data->m_status, NULL))
	{
		printf("Mutex init failed\n");
		return (1);
	}
	if (!data->cnt || !data->t2d || !data->t2e || !data->t2s \
	|| (argc == 6 && !data->meals) || !data->start)
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

	if (argc < 5 || argc > 6)
	{
		printf("Number of arguments must be 4 or 5\n");
		return (1);
	}
	if (validate_argv(argv) || init_data(&data, argc, argv))
		return (1);
	ph = (t_philo *)malloc(sizeof(t_philo) * data.cnt);
	if (ph == NULL)
	{
		printf("Malloc for philo structure failed\n");
		return (1);
	}
	if (init_philo(ph, &data))
		return (1);
	free(ph);
	return (0);
}

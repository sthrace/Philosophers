#include "philo.h"

void	ft_usleep(uint64_t time)
{
	uint64_t	timer;

	timer = ft_get_time();
	while ((ft_get_time() - timer) < time)
		usleep(time / 10);
}

uint64_t	ft_get_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		ft_exit(5);
	return (time.tv_sec * (uint64_t)1000000 + time.tv_usec);
}

void	ft_printer(t_philo *philo, char *str)
{
	uint64_t	now;

	now = ft_get_time() - philo->data->start;
	printf("%lu %d %s\n", now, philo->number, str);
}

void	ft_meal_counter(t_philo *temp)
{
	temp->got_food++;
	if (temp->got_food == temp->data->eat_cnt)
		temp->data->satisfied++;
}

int	ft_atoi_philo(char *nb, int type)
{
	long	res;
	int		i;

	i = -1;
	res = 0;
	while (nb[++i])
		if (nb[i] != ' ' && nb[i] != '+' && nb[i] < '0' && nb[i] > 9)
			ft_exit(3);
	i = 0;
	while (nb[i] == ' ' && nb[i] == '+')
		i++;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		res = res * 10 + nb[i] - 48;
		i++;
	}
	if (type == 1 && (res < 1 || res > 200))
		ft_exit(4);
	if (nb[i])
		ft_exit(3);
	return (res);
}
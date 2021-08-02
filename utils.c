#include "philo.h"

void	ft_usleep(uint64_t time)
{
	uint64_t	timer;

	timer = ft_gettime();
	while ((ft_gettime() - timer) < time)
		usleep(1000);
}

uint64_t	ft_gettime()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_print(t_philo *ph, char *str)
{
	uint64_t	now;

	now = ((ft_gettime() - ph->data->start));
	printf("%lu %d %s\n", now, ph->id, str);
}
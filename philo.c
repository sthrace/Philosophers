#include "philo.h"

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	int	i;

	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
}

void	ft_init(t_all *all, int argc, char **argv)
{
	all->forks = (t_forks *)malloc(sizeof(t_forks) * argc);
	all->philo = (t_philo *)malloc(sizeof(t_philo) * argc);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		return (1);
	ft_init(&all, argc, argv);
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL))
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL))
		return (1);
	if (pthread_join(t1, NULL))
		return (1);
	if (pthread_join(t2, NULL))
		return (1);
	pthread_mutex_destroy(&mutex);
	printf("Mails: %d\n", mails);
	return (0);
}
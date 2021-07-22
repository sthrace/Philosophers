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
	all->args.numphilo = ft_atoi_philo(argv[1], 1);
	all->forks = (t_forks *)malloc(sizeof(t_forks) * all->args.numphilo);
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->args.numphilo);
	all->args.die = ft_atoi_philo(argv[2], 2);
	all->args.eat = ft_atoi_philo(argv[3], 2);
	all->args.sleep = ft_atoi_philo(argv[4], 2);
	if (argc == 6)
		all->args.nummeals = ft_atoi_philo(argv[5], 2);
}

int	main(int argc, char **argv)
{
	t_all	*all;
	int		i;

	if (argc < 5 || argc > 6)
	{
		write(2, "Must provide at 4 or 5 arguments\n",34);
		exit (1);
	}
	i = 1;
	while (argv[++i])
		ft_atoi_philo(argv[i], 2);
	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		return (1);
	ft_init(all, argc, argv);
	return (0);
}
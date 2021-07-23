#include "philo.h"

void	*ft_dinner(t_all *all)
{
	int	i;
	pthread_mutex_lock(all->forks[i]);
	pthread_mutex_unlock(all->forks[i]);
}

void	ft_begin(t_all *all)
{
	int	i;
	pthread_t	*philo_t;

	i = 0;
	while (i < all->args.numphilo)
	{
		pthread_create(&philo_t[i], NULL, ft_dinner(all), NULL);
		i++;
	}
}

void	ft_init(t_all *all, int argc, char **argv)
{
	int	i;

	i = 0;
	all->args.numphilo = ft_atoi_philo(argv[1], 1);
	all->args.die = ft_atoi_philo(argv[2], 2);
	all->args.eat = ft_atoi_philo(argv[3], 2);
	all->args.sleep = ft_atoi_philo(argv[4], 2);
	if (argc == 6)
		all->args.nummeals = ft_atoi_philo(argv[5], 2);
	all->forks = (t_forks **)malloc(sizeof(t_forks *) * all->args.numphilo);
	all->philo = (t_philo **)malloc(sizeof(t_philo *) * all->args.numphilo);
	if (!all->forks || !all->philo)
		exit(1);
	while (i < all->args.numphilo)
	{
		all->forks[i] = (t_forks *)malloc(sizeof(t_forks));
		all->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		all->philo[i]->number = i + 1;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_all	*all;

	if (argc < 5 || argc > 6)
		ft_exit(3);
	i = 1;
	while (argv[++i])
		ft_atoi_philo(argv[i], 2);
	all = (t_all *)malloc(sizeof(t_all));
	if (all == NULL)
		return (1);
	ft_init(all, argc, argv);
	ft_begin(all);
	return (0);
}
#include "philo.h"

void	ft_exit(int err)
{
	if (err == 1)
		write(2, "Argument must be a positive integer\n", 36);
	if (err == 2)
		write(2, "Provide valid number of pilosophers 1-200\n", 42);
	if (err == 3)
		write(2, "Must provide 4 or 5 arguments\n",34);
	if (err == 4)
		write(2, "Gettimeofday malfunction\n", 25);
	if (err == 5)
		write(2, "Malloc failure\n", 15);
	if (err == 6)
		write(2, "Pthread create failed\n", 22);
	if (err == 7)
		write(2, "Pthread mutex init failed\n", 26);
	if (err == 8)
		write(2, "Pthread join failed\n", 20);
	if (err == 9)
		write(1, "All philosophers ate\n", 21);
	exit (1);
}

void	ft_init_struct(t_all *all, int argc, char **argv)
{
	all->data.philo_cnt = ft_atoi_philo(argv[1], 1);
	all->data.die = ft_atoi_philo(argv[2], 2) * 1000;
	all->data.eat = ft_atoi_philo(argv[3], 2) * 1000;
	all->data.sleep = ft_atoi_philo(argv[4], 2) * 1000;
	all->data.start = ft_get_time();
	all->data.eat_cnt = -1;
	all->data.death = 0;
	pthread_mutex_init(&all->data.print, NULL);
	if (argc == 6)
		all->data.eat_cnt = ft_atoi_philo(argv[5], 2);
	all->data.satisfied = 0;
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
	ft_pthread_init(all);
	return (0);
}
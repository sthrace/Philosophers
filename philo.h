#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct philo
{
	int		number;
	int		left;
	int		right;
}				t_philo;

typedef struct	fork
{
	pthread_mutex_t	*forks;
}				t_forks;

typedef struct	args
{
	int		die;
	int		eat;
	int		sleep;
	int		nummeals;
	int		numphilo;
}			t_args;

typedef struct all
{
	t_philo	**philo;
	t_forks	**forks;
	t_args	args;
}				t_all;

int	ft_atoi_philo(char *nb, int type);
void	ft_exit(int err);

#endif
#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct philo
{
	char	number;
	int		left;
	int		right;
}				t_philo;

typedef struct	fork
{
	pthread_mutex_t	*forks;
}				t_forks;

typedef struct all
{
	t_philo	*philo;
	t_forks	*forks;
}				t_all;

#endif
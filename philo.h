#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	thread;
	int			left;
	int			right;
	int			number;
	int			ate;
}				t_philo;


typedef struct s_data
{
	t_philo	*philo;
	int		philo_cnt;
	int		die;
	int		eat;
	int		sleep;
	int		eat_cnt;
}				t_data;


int		ft_atoi_philo(char *nb, int type);
void	ft_exit(int err);

#endif
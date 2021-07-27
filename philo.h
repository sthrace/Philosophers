#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>

typedef struct s_data
{
	int		philo_cnt;
	int		die;
	int		eat;
	int		sleep;
	int		eat_cnt;
	uint64_t		start;
}				t_data;
typedef struct s_philo
{
	pthread_t		thread;
	int				number;
	int				ate;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	t_data			*data;
}				t_philo;

typedef struct s_all
{
	t_philo	*philo;
	t_data	data;
}				t_all;


int		ft_atoi_philo(char *nb, int type);
void	ft_exit(int err);

#endif
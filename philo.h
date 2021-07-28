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
	int				philo_cnt;
	int				die;
	int				eat;
	int				sleep;
	int				eat_cnt;
	int				satisfied;
	int				death;
	uint64_t		start;
	pthread_mutex_t	print;
}				t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	int				number;
	int				got_food;
	uint64_t		start_meal;
	t_data			*data;
}				t_philo;

typedef struct s_all
{
	t_philo	*philo;
	t_data	data;
}				t_all;


int		ft_atoi_philo(char *nb, int type);
void	ft_exit(int err);
void	ft_printer(t_philo *philo, char *str);
uint64_t	ft_get_time();
void	ft_pthread_init(t_all *all);
void	*lifecycle(void *arg);
void	ft_eat(t_philo *temp);
void	ft_sleep(t_philo *temp);
void	ft_think(t_philo *temp);
void	ft_check_death(t_philo *philo);
void	ft_meal_counter(t_philo *temp);
void	ft_usleep(uint64_t time);

#endif
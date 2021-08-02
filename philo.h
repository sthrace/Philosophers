#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>

# define ALIVE 0
# define DEAD 1
# define FULL 2
typedef struct s_mutex
{
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_food;
	pthread_mutex_t	m_death;
}				t_mutex;
typedef struct s_data
{
	int				cnt;
	int				meals;
	int				status;
	int				full;
	int				t2d;
	int				t2e;
	int				t2s;
	uint64_t		start;
	
}				t_data;
typedef struct s_philo
{
	int				id;
	int				num_meals;
	uint64_t		last_meal;
	pthread_t		t_ph;
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	t_data			*data;
	t_mutex			*mutex;
}				t_philo;


// philo.c //

// init.c //

int	simulation_init(t_philo *ph, t_data *data, t_mutex *mutex);

// activity.c //

void	*lifecycle(void *arg);

// monitor.c //

void	food_counter(t_philo *ph);
void	checkdeath(t_philo *ph);

// utils.c //

void	ft_usleep(uint64_t time);
uint64_t	ft_gettime();
void	ft_print(t_philo *ph, char *str);

#endif
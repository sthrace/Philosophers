/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrace <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 09:53:26 by sthrace           #+#    #+#             */
/*   Updated: 2021/08/04 09:53:28 by sthrace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_t		t_death;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_food;
	pthread_mutex_t	m_death;
	pthread_mutex_t	m_status;	
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
}				t_philo;

// philo.c //

// activity.c //

int			thread_init(t_philo *ph, int i);
void		*lifecycle(void *arg);
void		ft_eat(t_philo *ph);

// monitor.c //

void		food_counter(t_philo *ph);
void		*deathcycle(void *arg);

// utils.c //

void		ft_usleep(uint64_t time);
uint64_t	ft_gettime(void);
void		ft_print(t_philo *ph, char *str);
void		mutex_destroy(t_philo *ph);

#endif

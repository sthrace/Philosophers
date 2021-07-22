#include "philo.h"

static void	ft_exit(int err)
{
	if (err == 1)
		write(2, "Argument must be a positive integer\n", 36);
	if (err == 2)
		write(2, "Provide valid number of pilosophers 1-200\n", 42);
	exit (1);
}

int	ft_atoi_philo(char *nb, int type)
{
	long	res;
	int		i;

	i = -1;
	res = 0;
	while (nb[++i])
		if (nb[i] != ' ' && nb[i] != '+' && nb[i] < '0' && nb[i] > 9)
			ft_exit(1);
	i = 0;
	while (nb[i] == ' ' && nb[i] == '+')
		i++;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		res = res * 10 + nb[i] - 48;
		i++;
	}
	if (type == 1 && (res < 1 || res > 200))
		ft_exit(2);
	if (nb[i])
		ft_exit(1);
	return (res);
}
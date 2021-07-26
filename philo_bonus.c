#include "philo_bonus.h"

int	main()
{
	pid_t	pid;
	int		x = 2;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		x++;
	sleep(2);
	printf("Value of x: %d\n", x);
	if (pid != 0)
		wait(NULL);
	return (0);
}
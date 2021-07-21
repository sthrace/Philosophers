#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		write(1, "Process\n", 8);
	if (pid != 0)
		wait(NULL);
	return (0);
}
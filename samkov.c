uint64_t	ft_get_time(void)
{
	uint64_t				to_return;
	static struct timeval	time;
	if (gettimeofday(&time, 0) < 0)
		return (0);
	to_return = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (to_return);
}
void	ft_fix_usleep(uint64_t msec)
{
	 uint64_t	start;
	 start = ft_get_time();
	 while (ft_get_time() - start < msec)
	 	usleep(500);
	usleep(msec *1000);
}
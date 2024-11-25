#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

// struct timeval {
// 	time_t		tv_sec;		// seconds from 1 January 1970
// 	suseconds_t tv_usec;	// microseconds from past second
// };

//int	gettimeofday(struct timeval *restrict tv, struct timezone *_Nullable restrict tz);
//returns 0 if success, -1 failure, receives the time struc and timezone applicable

// 1 seconds == 1000 miliseconds == 1000000 microseconds

size_t	get_current_time(void) //Returns the current time in miliseconds
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, int dead_flag)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

void	example1()
{
	struct timeval	time;

	printf("Example 1\n");
	gettimeofday(&time, NULL);
	printf("time.tv_sec: %li seconds passed since 01/01/1970\n", time.tv_sec);
	printf("time.tv_usec: %li microseconds passed since past second\n-----------\n", time.tv_usec);

	printf("%li hours passed since 1970\n", time.tv_sec / 60 / 60);
	printf("%li days passed since 1970\n", time.tv_sec / 60 / 60 / 24);
	printf("%li years passed since 1970\n", time.tv_sec / 60 / 60 / 24 / 365);
}


void	exmaple2()
{
	int	start;
	int	passed;

	start = get_current_time();
//	1 seconds == 1000 miliseconds == 1000000 microseconds
	usleep(3000000);	//microsecond
	passed = get_current_time() - start;
	printf("Passed: %i miliseconds\n", passed);
}

void	exmaple3()
{
	struct timeval	time_start;
	struct timeval	time_end;
	long			requested_time;
	long			actual_time;

	requested_time = 200 * 1000;	//200 miliseconds * microseconds
	gettimeofday(&time_start, NULL);
	usleep(requested_time);
	gettimeofday(&time_end, NULL);
	actual_time = (time_end.tv_sec - time_start.tv_sec) * 1000000 + (time_end.tv_usec - time_start.tv_usec);
	printf("Requested Time: %li\n", requested_time);
	printf("Time Passed: %li\n", actual_time);
}

int	main(void)
{
	//example1();
	exmaple2();
	//exmaple3();
}
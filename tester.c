#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <strings.h>
#include "../libft/libft.h"
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/resource.h>


int randint(int max)
{
	if (max < 1)
		return -1;
	if (max >= RAND_MAX)
		return rand();
	int end = RAND_MAX / max;
	end *= max;
	int ret;
	while ((ret = rand()) >= end);
	return ret % max;
}

int randintmin(int min, int max)
{
	if (max < 1 || min >= max)
		return -1;
	int ret;
	while ((ret = randint(max)) < min);
	return ret;
}

int main(void)
{
	srand((unsigned int)time(NULL));
	char str[20];
	for (int i = 0; i < 20; ++i)
		str[i] = randintmin(1, 127);
	
	printf("%zu\n", ft_strlen(str));
	
	/* code */
	return 0;
}

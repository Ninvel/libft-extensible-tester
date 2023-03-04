#include "tester.h"
#include "is_functests.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

#if defined ISALPHA
int source_of_truth(int arg)
{
	int libcret = isalpha(arg);
	int ftret = ft_isalpha(arg);
	return ((libcret == 0 ? ftret == libcret : ftret != 0) + '0');
}
#elif defined ISDIGIT
int source_of_truth();
#elif defined ISALNUM
int source_of_truth();
#elif defined ISASCII
int source_of_truth();
#elif defined ISPRINT
int source_of_truth();
#endif

// test compile this with gcc -g -DISALPHA is_functests.c tester.c -L../libft/ -lft
int main(void)
{
	srand((unsigned int)time(NULL));

	int fd = open("./tmp/test_results", O_APPEND | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IROTH);
	const int non_ascii_arg_num = NUMBER_OF_TESTS / 4;
	const int ascii_arg_num = NUMBER_OF_TESTS - non_ascii_arg_num;
	char results[ascii_arg_num + non_ascii_arg_num + 2];
	int args[ascii_arg_num + non_ascii_arg_num + 1];
	if (fd < 0)
	{
		perror("main");
		return (-1);
	}
	memset(results, -1, sizeof(results));
	results[ascii_arg_num + non_ascii_arg_num + 1] = '\n';
	args[ascii_arg_num + non_ascii_arg_num] = 0;
	for (int i = 0; i < ascii_arg_num; ++i)
		args[i] = randint(127);
	for (int i = ascii_arg_num; i < ascii_arg_num + non_ascii_arg_num; ++i)
		args[i] = randintmin(128, UCHAR_MAX);
	for (int i = 0; i < ascii_arg_num + non_ascii_arg_num + 1; ++i)
		results[i] = source_of_truth(args[i]);
	if (write(fd, results, ascii_arg_num + non_ascii_arg_num + 2) < 0)
		perror("main");
	close(fd);
	return (0);
}

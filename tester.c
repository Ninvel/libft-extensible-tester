#include <stdlib.h>
#include <limits.h>
#include <strings.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/resource.h>
#include <stdio.h>
#include "tester.h"
#include <assert.h>

int randint(int max)
{
	if (max < 1)
		return -1;
	if (max >= RAND_MAX)
		return rand();
	int end = RAND_MAX / max;
	end *= max;
	int ret;
	while ((ret = rand()) >= end)
		;
	return ret % max;
}

int randintmin(int min, int max)
{
	if (max < 1 || min >= max)
		return -1;
	int ret;
	while ((ret = randint(max)) < min)
		;
	return ret;
}

t_result_list *test_list_new()
{
	t_result_list *node = malloc(sizeof(t_result_list));
	if (node == NULL)
		perror("test_list_new");
	node->next = NULL;
	node->last = NULL;
	node->result.eq_test = -1;
	node->result.mem_test = -1;
	return node;
}

void test_list_add_back(t_result_list *last, t_result_list *node)
{
	if (last == NULL || node == NULL)
	{
		char *errstr = {"test_list_add_back received bad argument"};
		write(STDERR_FILENO, errstr, strlen(errstr));
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = node;
	node->last = last;
}

void test_list_free(t_result_list *list_head)
{
	t_result_list *delnode;
	while (list_head != NULL)
	{
		delnode = list_head;
		list_head = list_head->next;
		free(delnode);
	}
}

int main(void)
{
	srand((unsigned int)time(NULL));

	t_result_list *results = test_isalpha();

	for (t_result_list *node = results; node != NULL; node = node->next)
		printf("%s with arg %d | LIBC: %d | FT: %d\n", node->result.eq_test != 0 ? "PASSED" : "FAILED", node->result.serializedarg, node->result.serialized_libc_test, node->result.serialized_ft_res);
	test_list_free(results);

	/* code */
	return 0;
}

#include "tester.h"
#include <stdio.h>
#include <ctype.h>

#define ARGSIZE 1000
#define ASCIIMAX 127

void eq_test_isfunc(t_test_result *result, int (*lib_isfunc)(int), int (*ft_isfunc)(int), int arg)
{
	int ft_res = lib_isfunc(arg);
	int libc_res = ft_isfunc(arg);
	result->eq_test = (ft_res == libc_res);
	result->serializedarg = (int)arg;
	result->serialized_ft_res = ft_res;
	result->serialized_libc_test = libc_res;
	return;
}

t_result_list *test_isalpha()
{
	char testargs[ARGSIZE];
	t_result_list *results = test_list_new();
	for (int i = 0; i < ARGSIZE - 1; ++i)
		testargs[i] = randintmin(1, ASCIIMAX);
	testargs[ASCIIMAX - 1] = 0;
	eq_test_isfunc(&results->result, isalpha, ft_isalpha, testargs[0]);
	t_result_list *last_node = results = test_list_new();
	t_result_list *new_node;
	for (int i = 1; i < ARGSIZE; ++i)
	{
		new_node = test_list_new();
		eq_test_isfunc(&new_node->result, isdigit, ft_isdigit, testargs[i]);
		test_list_add_back(last_node, new_node);
		last_node = new_node;
	}
	return results;
}
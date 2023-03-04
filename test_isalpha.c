#include "tester.h"
#include <stdio.h>
#include <ctype.h>

#define ARGSIZE 1000
#define ASCIIMAX 127

enum Test_IsFunc
{
	TEST_ISALPHA = 0,
};

char isalpha_truth(int ftret, int arg)
{
	char libcret = isalpha(arg);
	return (libcret == 0 ? libcret == arg : arg != 0);
}

char isfunc_truth(enum Test_IsFunc id, int ftret, int arg)
{
	if (id == TEST_ISALPHA)
		return (isalpha_truth(ftret, arg));
	else
		return 0; // tmp
}

void eq_test_isfunc(t_test_result *result, char (*isfunc_truth)(int, int), int (*ft_isfunc)(int), int arg)
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
		eq_test_isfunc(&new_node->result, isalpha, ft_isalpha, testargs[i]);
		test_list_add_back(last_node, new_node);
		last_node = new_node;
	}
	return results;
}
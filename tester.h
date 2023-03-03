#ifndef TESTER_H
#define TESTER_H

#include "../libft/libft.h"

typedef struct s_test_result
{
	char eq_test;
	char mem_test;
	int serializedarg;
	int serialized_ft_res;
	int serialized_libc_test;
} t_test_result;

typedef struct s_result_list
{
	struct s_test_result result;
	struct s_result_list *next;
	struct s_result_list *last;
} t_result_list;

t_result_list *test_list_new();
void test_list_add_back(t_result_list *last, t_result_list *node);
void test_list_free(t_result_list *list_head);

int randintmin(int min, int max);
// void test_isfunc(t_test_result *result, int (*lib_isfunc)(int), int (*ft_isfunc)(int), int arg);
t_result_list *test_isalpha();

#endif
#include "corewar.h"
#include "libft.h"
#include "ft_printf.h"
#include "stdio.h"

typedef struct s_test
{
	int key;
	int value;
}			t_test;

int main()
{

	int test;
	int key;
	int value;
	t_heap *heap;

	t_test a1= {0,12};
	t_test a2={0,1};
	t_test a3={1,12};
	t_test a4={12, 0};
	t_test ptr;
	heap = NULL;

	heap = ft_heap_add(heap, ft_wrap_heap(a1.key, &a1));
	heap = ft_heap_add(heap, ft_wrap_heap(a2.key, &a2));
	heap = ft_heap_add(heap, ft_wrap_heap(a3.key, &a3));
	heap = ft_heap_add(heap, ft_wrap_heap(a4.key, &a4));
	int i = 1;
	while (heap)
	{
		value =( (t_test *) ft_pop_min_heap(&heap, &key))->value;
		ft_printf("%d key: %d value: %d\n", i++, key, value);
	}





}
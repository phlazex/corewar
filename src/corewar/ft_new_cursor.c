#include "corewar.h"

t_cursor *ft_new_cursor()
{
	t_cursor *cursor;

	if (!(cursor = (t_cursor*)malloc(sizeof(*cursor))))
		return (NULL);
	ft_bzero(cursor, sizeof(*cursor));
	return cursor;
}
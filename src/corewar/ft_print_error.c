#include "ft_printf.h"

void ft_print_error(int err)
{
	if (err == 1)
		ft_printf_fd(2, "Test error\n");
}
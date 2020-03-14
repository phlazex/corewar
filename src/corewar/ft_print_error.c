#include "ft_printf.h"
#include "corewar.h"

void ft_print_error(int err)
{
	ft_logo();
	ft_printf(E"196m");
	if (err == 1)
		ft_printf_fd(2, "Test error\n");
}
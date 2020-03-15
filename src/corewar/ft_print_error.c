#include <zconf.h>
#include "ft_printf.h"
#include "corewar.h"

void ft_print_error(t_err err)
{
	ft_logo();
	ft_printf(E"196m");
	ft_printf_fd(STDERR_FILENO, "Error: ");
	if (err == no_memory)
		ft_printf_fd(STDERR_FILENO, "Memory allocation error\n");
	else if (err == w_flag)
		ft_printf_fd(STDERR_FILENO, "Invalid option, run with no arguments for help\n");
	else if (err == w_file_name)
		ft_printf_fd(STDERR_FILENO, "Invalid file name, follow <name>.cor format\n");
	else if (err == w_player_number)
		ft_printf_fd(STDERR_FILENO,"Invalid player number, maximal possible players equal %d\n", MAX_PLAYERS);
	else if (err == w_format)
		ft_printf_fd(STDERR_FILENO, "Invalid input format, run with no arguments for help\n");
	ft_printf(RESET);
}
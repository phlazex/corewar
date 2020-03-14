#include "ft_printf.h"
#include "corewar.h"


int main(int argc, char **argv)
{
	if (argc > 1)
	{

	}
	else if (argc == 1)
		ft_usage();
	else if (argc > 16)
		ft_print_error(1);
	return 0;
}

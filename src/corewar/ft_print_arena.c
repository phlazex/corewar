#include "libft.h"
#include "ft_printf.h"
#include "corewar.h"

void ft_print_arena(void *arena, size_t size)
{
	if (size)
		while (size--)
		{
			ft_printf("%02x ", *(unsigned char*)arena);
			++arena;
			if ((size % 4) == 0)
				ft_printf("  ");
			if (!(size % 64))
				ft_printf("\n");
		}
}
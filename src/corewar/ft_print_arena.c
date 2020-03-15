#include "libft.h"
#include "ft_printf.h"
#include "corewar.h"

void ft_print_arena(void *arena)
{
	size_t size;

	size = MEM_SIZE;
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

void ft_print_regs(t_game *game)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
//		ft_printf("r%d: %x ",i + 1, game->regs[i]);
		i++;
	}
	ft_printf("\n\n");
}
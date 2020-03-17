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

static void ft_print_hex(void *data, void *end, void *mark, void *tail)
{
	int i;

	i = 16;
	while (i--)
	{
		if (data < end )
			ft_printf("%02x", *(unsigned char *) data);
		else
			ft_printf("  ");
		data ++;
		if (data == mark)
			ft_printf(RESET);
		if (data == tail)
			ft_printf(GRAY);

		if (i % 2 == 0)
			ft_printf(" ");
	}
	ft_printf(RESET);
}

static void ft_print_str(void *data, void *end, void *mark, void *tail)
{
	int i;

	i = 16;
	ft_printf("%4s", " ");
	while (i--)
	{
		if (data < end)
		{
			if (ft_isprint(*(unsigned char *) data))
				ft_printf("%c", *(unsigned char *) data);
			else
				ft_printf(".");
			data++;
			if (data == mark)
				ft_printf(RESET);
			if (data == tail)
				ft_printf(GRAY);
		}
		else
			ft_printf(" ");

	}
	ft_printf("\n");
}

void ft_print_memory(void *start, void *end, void *mark, void *tail)
{
	int i;

	i = 0;

	while (start <= end)
	{
		ft_printf(BLUE"%04x0: "RESET,i);
		if (start < mark)
			ft_printf(GREEN);
		if (start > tail)
			ft_printf(GRAY);
		ft_print_hex(start, end, mark, tail);
		if (start < mark)
			ft_printf(GREEN);
		if (start > tail)
			ft_printf(GRAY);
		ft_print_str(start, end, mark, tail);
		start += 16;
		i++;
	}
	ft_printf("\n");
}
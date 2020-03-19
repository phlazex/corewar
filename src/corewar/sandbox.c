#include "corewar.h"
#include "libft.h"
#include "ft_printf.h"
#include "stdio.h"

#include "ft_battle.c"
int main()
{
	char op = 0x04;
	unsigned char type = 0xb6;
	int next = 0;
	ft_printf("\"%s\" (%d): %08b\n", op_tab[op - 1].name, op, type);
	ft_printf("%d\n",ft_check_types(&type, op , &next));
	ft_printf("%d\n", next);
}
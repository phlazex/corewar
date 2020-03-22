#include "corewar.h"
#include "libft.h"
#include "ft_printf.h"
#include "stdio.h"

int main()
{
	char op = 0x04;
	unsigned char type = 0xb6;
	int next =0x0100;
	uint32_t test = 0x456711ff;
	t_vm nbr;
	nbr.value = 0x78fffe;
//	ft_printf("\"%s\" (%d): %08b\n", op_tab[op - 1].name, op, type);
//	ft_printf("%d\n",ft_check_types(&type, op , &next));
	ft_printf("1:%d\n", -1123 % IDX_MOD);
	test = test >> 8u;
	ft_printf("2:%d\n", IDX_MOD);
	test = test >> 8u;
	ft_printf("3:%d\n", IDX_MOD - 99 );
	test = test >> 8u;
	ft_printf("4:%d\n", ft_mod(-1123, IDX_MOD));
	ft_printf("4:%d\n", (-1123 + 3*IDX_MOD) % IDX_MOD);





}
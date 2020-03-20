#include "corewar.h"
#include "libft.h"
#include "ft_printf.h"
#include "stdio.h"

int main()
{
	char op = 0x04;
	unsigned char type = 0xb6;
	int next =0x0100;
	unsigned int test = -33;
	t_vm nbr;
	nbr.value = 0xfe000001;
//	ft_printf("\"%s\" (%d): %08b\n", op_tab[op - 1].name, op, type);
//	ft_printf("%d\n",ft_check_types(&type, op , &next));
	ft_printf("1:%d\n", nbr.v_1);
	ft_printf("2:%d\n", nbr.v_2);
	ft_printf("4:%d\n", nbr.v_4);




}
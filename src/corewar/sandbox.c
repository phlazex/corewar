#include "corewar.h"
#include "libft.h"
#include "ft_printf.h"
#include "stdio.h"

int main()
{
	unsigned char str[] = {13, 255 ,15, 15, 0, 255, 12, 00};
	ft_printf("%#.16lx\n", ft_atoin(str, 8));
}
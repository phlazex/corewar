#include "libft.h"
#include "corewar.h"

u_int64_t ft_atoin(void* data, size_t size)
{
	u_int64_t value;

	if (size > 8)
		return (-1);
	value = 0;
	while (size--)
	{
		value = value << 8u;
		value += *(unsigned char*)data++;
	}
	return value;
}

//int32_t ft_atoi_vm(void* head, size_t *address, size_t size)
//{
//	u_int32_t value;
//
//	if (size > 8)
//		return (-1);
//	value = 0;
//	while (size--)
//	{
//		value = value << 8u;
//		value += *(char*)(head + *address);
//		*address = (*address + 1) % MEM_SIZE;
//	}
//	return value;
//}

t_vm ft_atoi_vm(void* head, size_t *address, size_t size)
{
	t_vm	nbr;
	u_int32_t value;
	value = 0;
	while (size--)
	{
		value = value << 8u;
		value += *(unsigned char*)(head + ft_mod((*address)++, MEM_SIZE));
	}
	*address = ft_mod(*address, MEM_SIZE);
	nbr.value = value;
	return nbr;
}

void ft_itoa_vm(void *head, int32_t address, int32_t value)
{
	int size;

	size = DIR_SIZE;
	while (size--)
	{
		*(unsigned char*)(head + ft_mod(address + size, MEM_SIZE)) = (unsigned char)value;
		value = value >> 8u;
	}

}
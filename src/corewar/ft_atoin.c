#include "libft.h"

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
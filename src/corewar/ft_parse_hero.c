#include "corewar.h"

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>

t_err ft_parse_hero(t_hero *hero, t_mem *mem)
{
	u_int32_t magic;

	if (mem->end - mem->head < PROG_NAME_LENGTH + COMMENT_LENGTH + 3 + 8)
		return (w_file_size);
	mem->current = mem->head;
//	magic = ft_atoi()
	printf("\n%#0x", *(unsigned char *)mem->current);
	printf("%x", *(unsigned char *)(mem->current +1));
	printf("%x", *(unsigned char *)(mem->current+2));
	printf("%x\n", *(unsigned char *)(mem->current+3));
	printf("%d\n", COREWAR_EXEC_MAGIC);
	printf("%s\n", ft_itoa(COREWAR_EXEC_MAGIC));
	printf("%#0x\n", magic);
	if (COREWAR_EXEC_MAGIC != magic)
		return (except_magic);
	hero->header->prog_size = mem->end - mem->head - PROG_NAME_LENGTH - COMMENT_LENGTH - 11;

	write(1, mem->head, mem->end - mem->head);
	return (success);

//COREWAR_EXEC_MAGIC
}
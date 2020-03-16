#include "corewar.h"

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>

t_err ft_parse_hero(t_hero *hero, t_mem *mem)
{
	u_int32_t magic;

	if (mem->end - mem->head < PROG_NAME_LENGTH + COMMENT_LENGTH + 4 + 8)
		return (w_file_size);
	mem->current = mem->head;
	if (COREWAR_EXEC_MAGIC != ft_atoin(mem->current, 4))
		return (except_magic);
	hero->header.prog_size = mem->end - mem->head - PROG_NAME_LENGTH - COMMENT_LENGTH - 12;

	write(1, mem->head, mem->end - mem->head);
	return (success);

//COREWAR_EXEC_MAGIC
}
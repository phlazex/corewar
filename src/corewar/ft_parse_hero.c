#include "corewar.h"

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>

t_err ft_parse_hero(t_hero *hero, t_mem *mem)
{
	if (mem->end - mem->head < PROG_NAME_LENGTH + COMMENT_LENGTH + 4 + 8)
		return (w_file_size);
	mem->current = mem->head;
	if (COREWAR_EXEC_MAGIC != ft_atoin(mem->current, 4))
		return (except_magic);
	mem->current += 4;
	ft_memcpy(hero->header.prog_name, mem->current, PROG_NAME_LENGTH);
	mem->current += PROG_NAME_LENGTH + 4;
	hero->header.prog_size = ft_atoin(mem->current, 4);
	if (hero->header.prog_size > CHAMP_MAX_SIZE)
		return (exceed_size);
	mem->current += 4;
	if (hero->header.prog_size != mem->end - mem->current - COMMENT_LENGTH - 4)
		return (wrong_psize);
	ft_memcpy(hero->header.comment, mem->current, COMMENT_LENGTH);
	mem->current += COMMENT_LENGTH + 4;
	ft_memcpy(hero->program, mem->current, hero->header.prog_size);
//	ft_print_memory(hero->program, hero->program + CHAMP_MAX_SIZE, hero->program, hero->program + CHAMP_MAX_SIZE);
//	ft_print_memory(mem->head, mem->end, mem->cursor, mem->end);
	return (success);

//COREWAR_EXEC_MAGIC
}
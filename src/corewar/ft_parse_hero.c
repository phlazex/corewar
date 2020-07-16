/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_hero.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_printf.h"

t_err	ft_parse_hero(t_hero *hero, t_mem *mem)
{
	if (mem->end - mem->head < PROG_NAME_LENGTH + COMMENT_LENGTH + 4 + 8)
		return (w_file_size);
	mem->current = mem->head;
	hero->header.magic = ft_atoin(mem->current, 4);
	if (COREWAR_EXEC_MAGIC != hero->header.magic)
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
	return (success);
}

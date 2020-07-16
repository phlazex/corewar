/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "vis.h"
#include "corewar_op.h"
#include <unistd.h>

static t_bool	ft_check_arg(t_game *game, unsigned char type, char index)
{
	int32_t	value;
	int32_t	op;

	op = game->cursor->op - 1;
	if (type == REG_CODE)
	{
		value = ft_atoi_vm(game->arena, &game->cursor->current, TYPE_LEN).v_1;
		if ((g_op_tab[op].types[index] & 1) && value > 0 && value < 0x11)
			return (true);
	}
	if (type == DIR_CODE)
	{
		game->cursor->current += g_op_tab[op].dir_size;
		game->cursor->current = ft_mod(game->cursor->current, MEM_SIZE);
		if (g_op_tab[op].types[index] & 2)
			return (true);
	}
	if (type == IND_CODE)
	{
		game->cursor->current += IND_SIZE;
		game->cursor->current = ft_mod(game->cursor->current, MEM_SIZE);
		if (g_op_tab[op].types[index] & 4)
			return (true);
	}
	return (false);
}

static t_bool	ft_check_types(t_game *game)
{
	union u_types	type;
	int32_t			op;
	t_bool			ok;
	t_cursor		*cursor;

	cursor = game->cursor;
	op = cursor->op - 1;
	cursor->current = (cursor->pc + OP_LEN) % MEM_SIZE;
	type.value = ft_atoi_vm(game->arena, &cursor->current, TYPE_LEN).v_1;
	ok = ft_check_arg(game, type.args.arg1, 0);
	if (g_op_tab[op].arg_count > 1)
		ok = ft_check_arg(game, type.args.arg2, 1) && ok;
	if (g_op_tab[op].arg_count > 2)
		ok = ft_check_arg(game, type.args.arg3, 2) && ok;
	if (type.args.arg4)
		ok = false;
	if (!ok)
		cursor->pc = cursor->current;
	return (ok);
}

static t_err	ft_apply_op(t_game *game)
{
	t_err	err;
	size_t	temp;

	if (game->input->log)
		temp = game->cursor->pc;
	err = g_op_tab[((t_cursor*)game->cursor)->op - 1].func(game);
	game->cursor->pc = game->cursor->current;
	if (game->input->log)
		ft_log_cursor(game, temp);
	return (err);
}

t_err			ft_execute(t_game *game)
{
	t_cursor	*cursor;
	t_err		err;

	err = success;
	cursor = game->cursor;
	if (cursor->op > 0x00 && cursor->op < 0x11)
	{
		if (g_op_tab[cursor->op - 1].arg_type)
		{
			if (ft_check_types(game))
				err = ft_apply_op(game);
		}
		else
			err = ft_apply_op(game);
	}
	else
		cursor->pc = (cursor->pc + OP_LEN) % MEM_SIZE;
	return (err);
}

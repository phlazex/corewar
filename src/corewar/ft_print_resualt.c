/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_resualt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "ft_printf.h"

void	ft_print_result(t_game *game)
{
	if (game->winner)
	{
		ft_set_color(white + game->winner->id);
		ft_printf("! Congratulations to the winning player %d, "
			"weighting %d bytes, \"%s\" (\"%s\") !\n"RESET,
			game->winner->id,
			game->winner->header.prog_size,
			game->winner->header.prog_name,
			game->winner->header.comment);
	}
}

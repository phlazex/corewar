/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "mlx.h"
#include <stdlib.h>

void	ft_delete_window(t_window **window)
{
	if (!*window)
		return ;
	mlx_destroy_window((*window)->mlx, (*window)->win);
	if ((*window)->mlx)
		free((*window)->mlx);
	free((*window)->colors);
	if ((*window)->game)
		ft_game_over(&(*window)->game);
	free(*window);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int	ft_check_color(int color)
{
	if (color == blue)
		return (C_RED);
	if (color == green)
		return (C_YELLOW);
	if (color == purple)
		return (C_GREEN);
	if (color == red)
		return (C_BLUE);
	if (color == grey)
		return (C_DGRAY);
	if (color == i_blue || color == l_blue)
		return (C_IRED);
	if (color == i_green || color == l_green)
		return (C_IYELLOW);
	if (color == i_purple || color == l_purple)
		return (C_IGREEN);
	if (color == i_red || color == l_red)
		return (C_IBLUE);
	if (color == i_grey)
		return (C_LGRAY);
	return (C_DGRAY);
}

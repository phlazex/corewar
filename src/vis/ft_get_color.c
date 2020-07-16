/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayooden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by ayooden           #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by ayooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_get_light(int begin, int end, double percent)
{
	int	new_color;

	new_color = (int)((1.0 - percent) * begin) + (int)(percent * end);
	return (new_color);
}

int			ft_get_color(int begin_color, int end_color, double percent)
{
	int	red;
	int	green;
	int	blue;
	int	new_color;

	red = ft_get_light(((begin_color >> 16) & 0xff), \
	((end_color >> 16) & 0xff), percent);
	green = ft_get_light(((begin_color >> 8) & 0xff), \
	((end_color >> 8) & 0xff), percent);
	blue = ft_get_light((begin_color & 0xff), \
	(end_color & 0xff), percent);
	new_color = (red << 16) | (green << 8) | blue;
	return (new_color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "corewar.h"

int			ft_set_color(t_color color)
{
	ft_printf(RESET);
	if (color == white)
		return (ft_printf(RESET));
	if (color == grey)
		return (ft_printf(GRAY));
	if (color == green)
		return (ft_printf(GREEN));
	if (color == red)
		return (ft_printf(RED));
	if (color == blue)
		return (ft_printf(BLUE));
	if (color == purple)
		return (ft_printf(MAGENTA));
	if (color == i_green)
		return (ft_printf(IGREEN));
	if (color == i_red)
		return (ft_printf(IRED));
	if (color == i_blue)
		return (ft_printf(IBLUE));
	if (color == i_purple)
		return (ft_printf(IMAGENTA));
	return (0);
}

void		ft_print_arena(t_game *game)
{
	size_t	i;
	void	*temp;
	t_color	old_color;

	temp = game->arena;
	i = 0;
	old_color = game->color[0];
	ft_set_color(old_color);
	while (i < MEM_SIZE)
	{
		if (game->color[i] != old_color)
		{
			ft_set_color(game->color[i]);
			old_color = game->color[i];
		}
		ft_printf("%02x", *(unsigned char*)temp);
		++temp;
		i++;
		if ((i % 2) == 0)
			ft_printf(" ");
		if (!(i % 64))
			ft_printf("\n");
	}
	ft_printf(RESET);
}

static void	ft_print_hex_fd(int fd, void *data, void *end)
{
	int	i;

	i = 16;
	while (i--)
	{
		if (data < end)
			ft_printf_fd(fd, "%02x", *(unsigned char *)data);
		else
			ft_printf_fd(fd, "  ");
		data++;
		if (i % 2 == 0)
			ft_printf_fd(fd, " ");
	}
}

void		ft_print_memory_fd(int fd, void *start, void *end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		ft_print_hex_fd(fd, start, end);
		start += 16;
		i++;
	}
	ft_printf_fd(fd, "\n");
}

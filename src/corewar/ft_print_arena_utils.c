/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arena_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_print_hex(void *data, void *end, void *mark, void *tail)
{
	int	i;

	i = 16;
	while (i--)
	{
		if (data < end)
			ft_printf("%02x", *(unsigned char *)data);
		else
			ft_printf("  ");
		data++;
		if (data == mark)
			ft_printf(RESET);
		if (data == tail)
			ft_printf(GRAY);
		if (i % 2 == 0)
			ft_printf(" ");
	}
	ft_printf(RESET);
}

void	ft_print_str(void *data, void *end, void *mark, void *tail)
{
	int	i;

	i = 16;
	ft_printf("%4s", " ");
	while (i--)
	{
		if (data < end)
		{
			if (ft_isprint(*(unsigned char *)data))
				ft_printf("%c", *(unsigned char *)data);
			else
				ft_printf(".");
			data++;
			if (data == mark)
				ft_printf(RESET);
			if (data == tail)
				ft_printf(GRAY);
		}
		else
			ft_printf(" ");
	}
	ft_printf("\n");
}

void	ft_print_memory(void *start, void *end, void *mark, void *tail)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		if (start < mark)
			ft_printf(GREEN);
		if (start > tail)
			ft_printf(GRAY);
		ft_print_hex(start, end, mark, tail);
		if (start < mark)
			ft_printf(GREEN);
		if (start > tail)
			ft_printf(GRAY);
		ft_print_str(start, end, mark, tail);
		start += 16;
		i++;
	}
	ft_printf("\n");
}

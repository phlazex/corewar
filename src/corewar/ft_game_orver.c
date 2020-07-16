/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_orver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

void	*ft_game_over(t_game **game)
{
	if (!game || !(*game))
		return (NULL);
	if ((*game)->arena)
		ft_memdel((void**)&(*game)->arena);
	while ((*game)->head)
	{
		(*game)->cursor = (*game)->head->next;
		ft_memdel((void**)&(*game)->head);
		(*game)->head = (*game)->cursor;
	}
	ft_memdel((void**)game);
	return (NULL);
}

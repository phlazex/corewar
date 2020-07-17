/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_heroes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
#include <zconf.h>
#include "libft.h"

static t_err	ft_get_hero(t_hero *hero)
{
	t_mem	*mem;
	t_err	err;
	int		fd;

	err = success;
	if ((fd = open(hero->file_name, O_RDONLY)) <= 0)
		return (no_file);
	if (!(mem = ft_init_memory()))
		return (no_memory);
	if (fast_read_in_memory(fd, mem) == -1)
		err = w_file_read;
	if (!err)
		err = ft_parse_hero(hero, mem);
	ft_memdel((void**)&mem->head);
	ft_memdel((void**)&mem);
	close(fd);
	return (err);
}

t_err			ft_get_heroes(t_data *data)
{
	int	i;
	int	err;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (data->hero_list[i].id)
			if ((err = ft_get_hero(data->hero_list + i)))
				return (err);
		++i;
	}
	return (success);
}

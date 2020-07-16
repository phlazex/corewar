/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_heroes_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>
#include "libft.h"

/*
**	0x726f632e == "./cor"
*/

t_err		ft_check_file_name(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 3)
		return (w_file_name);
	if (*(int32_t*)(file_name + len - 4) == 0x726f632e)
		return (success);
	return (w_format);
}

t_err       ft_fill_hero_list(int argc, char **argv, t_data *data) {
    int i;
    int j;
	t_err  err;

	err = success;
    i = 0;
    while (++i < argc) {
        if (!ft_strcmp(argv[i], "-n"))
            i += 2;
        else if ((err = ft_check_file_name(argv[i]))) {
            j = -1;
            while (++j < MAX_PLAYERS)
                if (data->hero_list[j].id == 0) {
                    data->hero_list[j].id = j + 1;
                    data->hero_list[j].file_name = argv[i];
                    break;
                }
            if (j == MAX_PLAYERS)
                return (w_player_number);
        }
    }
    return (err);
}

t_err		ft_get_heroes_files(int argc, char **argv, t_data *data)
{
	int	i;
	int	index;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-n"))
		{
			index = ft_atoi(argv[++i]);
			if (data->hero_list[index - 1].id)
				return (dup_id);
			data->hero_list[index - 1].id = index;
			data->hero_list[index - 1].file_name = argv[++i];
		}
	}
	return ft_fill_hero_list(argc, argv, data);
}

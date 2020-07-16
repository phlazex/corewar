/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <zconf.h>
#include "libft.h"

t_err			ft_is_correct_number(const char *number)
{
	if (number == NULL || *number == 0 || *(number + 1))
		return (w_player_number);
	if (*number == '1' || *number == '2' || *number == '3' || *number == '4')
		return (success);
	return (w_player_number);
}

static void		ft_init_data(t_data *data)
{
	ft_bzero(data, sizeof(*data));
	data->dump = -1;
	data->vis_on = false;
}

t_err			ft_parse_input(int argc, char **argv, t_data **data)
{
	t_err	err;

	if (!(*data = (t_data*)malloc(sizeof(**data))))
		return (no_memory);
	ft_init_data(*data);
	if ((err = ft_check_opt(argc, argv, *data)))
		return (err);
	if ((err = ft_get_heroes_files(argc, argv, *data)))
		return (err);
	if ((err = ft_get_heroes(*data)))
		return (err);
	return (success);
}

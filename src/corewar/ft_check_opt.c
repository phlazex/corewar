/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_opt.c                                     :+:      :+:    :+:   */
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
t_err	ft_checker_helper(int32_t argc, char **argv, t_data *data, int *i){
	int j;
	t_err err;

	j = MAX_OPT;
	while (j--)
	{
		if (!ft_strcmp(argv[*i], opt_tab[j].name))
		{
			if ((err = opt_tab[j].f(argc, i, argv, data)))
				return (err);
			break ;
		}
	}
	return (success);
}

t_err	ft_check_opt(int32_t argc, char **argv, t_data *data)
{
	t_err	err;
	int		i;
	int		j;

	i = 0;
	err = success;
	while (++i < argc)
	{
		if (!argv[i] || !argv[i][0])
			return (w_format);
		if (argv[i][0] == '-' && argv[i][1])
		{
            if ((err = ft_checker_helper(argc, argv, data, &i)))
                return err;
        }
		else if (i < argc)
		{
			if ((err = ft_check_file_name(argv[i])))
				return (w_file_name);
		}
		else
			err = w_format;
	}
	return (err);
}

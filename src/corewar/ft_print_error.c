/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "corewar.h"

static void	ft_print_error_2(int fd, t_err err)
{
	if (err == dup_id)
		ft_printf_fd(fd, "Duplicate player id\n");
	else if (err == no_file)
		ft_printf_fd(fd, "File not found\n");
	else if (err == w_file_read)
		ft_printf_fd(fd, "Can't read file\n");
	else if (err == w_file_size)
		ft_printf_fd(fd, "Incorrect file size\n");
	else if (err == except_magic)
		ft_printf_fd(fd, "Missing magic head\n");
	else if (err == exceed_size)
		ft_printf_fd(fd, "Program size exceeds maximum, Max size: %d b\n",\
		CHAMP_MAX_SIZE);
	else if (err == wrong_psize)
		ft_printf_fd(fd, \
		"The actual program size does not match the specified\n", \
		CHAMP_MAX_SIZE);
	ft_printf(RESET);
}

void		ft_print_error(t_err err)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_printf(E"196m");
	ft_printf_fd(fd, "Error: ");
	if (err == no_memory)
		ft_printf_fd(fd, "Memory allocation error\n");
	else if (err == w_flag)
		ft_printf_fd(fd, "Invalid option, run with no arguments for help\n");
	else if (err == w_file_name)
		ft_printf_fd(fd, "Invalid file name, follow <name>.cor format\n");
	else if (err == w_player_number)
		ft_printf_fd(fd,\
		"Invalid player number, maximal possible players equal %d\n", \
		MAX_PLAYERS);
	else if (err == w_format)
		ft_printf_fd(fd, \
		"Invalid input format, run with no arguments for help\n");
	else
		return (ft_print_error_2(fd, err));
	ft_printf(RESET);
}

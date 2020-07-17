/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 13:34:18 by hwolf             #+#    #+#             */
/*   Updated: 2020/03/17 13:34:19 by hwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include "ft_printf.h"
#include "corewar_op.h"
#include <time.h>
#include <fcntl.h>

static int	ft_log_add(char *name)
{
	int fd;

	if (name)
	{
		if ((fd = open(name, O_CREAT | O_TRUNC | O_RDWR)) <= 0)
			ft_printf("Can't create file!\n");
	}
	else
	{
		if ((fd = open("func.log", O_CREAT | O_TRUNC | O_RDWR)) <= 0)
			ft_printf("Can't create file!\n");
	}
	return (fd);
}

t_log		*ft_logger_init(char *name)
{
	t_log		*log;
	long int	ttime;
	clock_t		start_time;

	start_time = clock();
	ttime = time(NULL);
	if (!(log = (t_log*)malloc(sizeof(*log))))
		return (NULL);
	log->fd_cursor = ft_log_add(NULL);
	log->fd_game = ft_log_add("game.log");
	if (log && log->fd_cursor > 0)
	{
		log->start_time = start_time;
		log->current_time = start_time;
		log->string_nbr = 0;
		ft_printf_fd(log->fd_cursor, "\"CoreWar\" log at %s", ctime(&ttime));
	}
	if (log)
		ft_printf_fd(log->fd_game, "\"CoreWar\" log at %s", ctime(&ttime));
	return (log);
}

void		ft_log_cursor(t_game *g, size_t prev)
{
	t_cursor	*cursor;
	int			len;

	len = REG_NUMBER;
	if (g->cursor)
	{
		cursor = g->cursor;
		ft_printf_fd(g->log->fd_cursor, "%4d: id:%3d | %s | op:%3d (%5s)"
				" | lc: %s | (%4d->%-4d):%-3d [ ", g->total_cycles, \
				cursor->id, cursor->carry ? " true" : "false", cursor->op, \
				(cursor->op > 0 && cursor->op < 17) ? \
				g_op_tab[cursor->op - 1].name : " err ",
				cursor->alive ? " true" : "false", prev, cursor->current,
				(cursor->op > 0 && cursor->op < 17) ? \
				g_op_tab[cursor->op - 1].cycles : 1);
		while (len--)
			ft_printf_fd(g->log->fd_cursor, "%d ", cursor->regs[len]);
		ft_printf_fd(g->log->fd_cursor, "]\t");
		if (prev < cursor->current && cursor->current - prev < 10)
			ft_print_memory_fd(g->log->fd_cursor, g->arena + prev, \
			g->arena + cursor->current);
		else
			ft_print_memory_fd(g->log->fd_cursor, g->arena + prev, \
			g->arena + prev + 3);
	}
}

void		ft_log_game(t_game *game)
{
	ft_printf_fd(game->log->fd_game, "%5d: cycle: %4d cursors: "
	"%4d checks: %4d check live: %4d winner: %1d(%s) "
	"cycles to die: %d\n",
	game->total_cycles,
	game->cycle,
	game->cursors_count,
	game->checks_done + 1,
	game->check_live,
	game->winner ? game->winner->id : 0,
	game->winner ? game->winner->header.prog_name : "",
	game->cycles_to_die);
}

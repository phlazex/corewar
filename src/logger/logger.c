#include "corewar.h"
#include "libft.h"
#include "ft_printf.h"
#include <time.h>
#include <fcntl.h>

static int ft_log_add(char *name)
{
	int fd;

	if (name)
	{
		if ((fd = open(name, O_CREAT | O_TRUNC | O_RDWR)) <= 0)
			ft_printf("Can't create file!\n");
	}
	else
		if ((fd = open("../log.txt", O_CREAT | O_TRUNC | O_RDWR)) <= 0)
			ft_printf("Can't create file!\n");
	return fd;
}

t_log *ft_logger_init(char *name)
{
	t_log *log;
	long int ttime;
	clock_t start_time;

	start_time = clock();
	ttime = time(NULL);
	if (!(log = (t_log*)malloc(sizeof(*log))))
		return (NULL);
	log->fd_cursor = ft_log_add(NULL);
	log->fd_game = ft_log_add("../game.log");

	if(log && log->fd_cursor > 0)
	{
		log->start_time = start_time;
		log->current_time = start_time;
		log->string_nbr = 0;
		ft_printf_fd(log->fd_cursor, "\"CoreWar\" log at %s", ctime(&ttime));
	}
	if(log)
	{
		ft_printf_fd(log->fd_game, "\"CoreWar\" log at %s", ctime(&ttime));
	}
	return (log);
}

void ft_log(t_log *log, char *string)
{
	clock_t time;

	time = clock();

	if(log && log->fd_cursor > 0)
	{
//		ft_printf_fd(log->fd_cursor, "%4d: %5.1f:(%5.1f): %s\n",
//					 log->string_nbr++,
//					 (double) (time - log->start_time) / CLOCKS_PER_SEC * 1e3,
//					 (double) (time - log->current_time) / CLOCKS_PER_SEC * 1e3,
//					 string);
		ft_printf_fd(log->fd_cursor, "%4d: %s\n",
					 log->string_nbr++,
					 string);
		log->current_time = time;
	}
}

void ft_log_cursor(t_game *game)
{
	t_cursor * cursor;
	int len;

	len = REG_NUMBER;
	if (game->cursor)
	{
		cursor = (t_cursor *) game->cursor->content;
		ft_printf_fd(game->log->fd_cursor,
					 "%4d: id : %4d | carry: %s | op: %3d (%5s) | live_cycle: %4d | "
					 "current: %4d | ready: %3d [ ",
					 game->total_cycles,
					 cursor->id,
					 cursor->carry ? " true" : "false",
					 cursor->op,
					 (cursor->op > 0 && cursor->op < 17) ? op_tab[cursor->op - 1].name : " err ",
					 cursor->live_cycle,
					 cursor->current,
					 cursor->ready);

		while (len--)
			ft_printf_fd(game->log->fd_cursor, "%3d ", cursor->regs[len]);
		ft_printf_fd(game->log->fd_cursor, "]\n");
	}
}

void ft_log_game(t_game *game)
{
	ft_printf_fd(game->log->fd_game, "%5d: cycle: %4d cursors: %4d checks: %4d check live: %4d winner: %1d(%s) (live:%3d): live call: %d cycles to die: %d\n",
				 game->total_cycles,
				 game->cycle,
			game->cursors_count,
			game->checks_done,
			game->check_live,
			game->winner ? game->winner->id : 0,
			game->winner ? game->winner->header.prog_name : "",
			game->winner ? game->winner->live : 0,
				 game->check_live,
				 game->cycles_to_die);
}
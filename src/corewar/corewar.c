#include "ft_printf.h"
#include "corewar.h"

int main(int argc, char **argv)
{
	t_game *game;
	t_err err;
	t_data *data;
	ft_printf(CLR);
//	if (!(fd_game = ft_init_game()))
//		return (0); //memory allocated error

//	ft_print_regs(fd_game);
//	ft_print_arena(fd_game->arena);
	if (argc > 1 && argc < MAX_ARGS_NUMBER + MAX_PLAYERS + 2)
	{
		if ((err = ft_parse_input(argc, argv, &data)))
			ft_print_error(err);
//		ft_printf("%s\n", data->hero_list[0].header.prog_name);
//		ft_parse_hero();
		if (!(game = ft_init_game()))
			return (0); //memory allocated error
		ft_log(game->log,"Game created");

		if (err == success)
		{
			ft_past_heroes(game, data);
			if ((err = ft_init_cursors(game)))
				ft_print_error(err);
			ft_log(game->log,"Warrior gutted");
//			ft_print_arena(game);
			ft_printf("\n");
			ft_battle(game);
			ft_log(game->log,"Battle finished");
//			ft_print_arena(game);
			ft_print_result(game);

			ft_game_over(&game);
		}
	}
	else if (argc == 1)
		ft_usage();
	else
		;

	return 0;
}

#include "ft_printf.h"
#include "corewar.h"

int main(int argc, char **argv)
{
	t_game *game;
	t_err err;
	t_data *data;
	ft_printf(CLR);
//	if (!(game = ft_init_game()))
//		return (0); //memory allocated error

//	ft_print_regs(game);
//	ft_print_arena(game->arena);
	if (argc > 1 && argc < MAX_ARGS_NUMBER + MAX_PLAYERS + 2)
	{
		if ((err = ft_parse_input(argc, argv, &data)))
			ft_print_error(err);
//		ft_printf("%s\n", data->hero_list[0].header.prog_name);
//		ft_parse_hero();
		if (!(game = ft_init_game()))
			return (0); //memory allocated error


//		*(char*)(game->arena) = '.';
//		*(char*)(game->arena+1) = 'c';
//		*(char*)(game->arena+2) = 'o';
//		*(char*)(game->arena+3) = 'r';

		if (err == success)
		{
			ft_past_heroes(game, data);
			if ((err = ft_init_cursors(game)))
				ft_print_error(err);
			ft_battle(game);
//		ft_print_result();
			ft_print_arena(game);

			ft_game_over(&game);
		}
	}
	else if (argc == 1)
		ft_usage();
	else
		;

	return 0;
}

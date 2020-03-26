#include "ft_printf.h"
#include "corewar.h"

int main(int argc, char **argv)
{
	t_game *game;
	t_err err;
	t_data *data;

	ft_printf(CLR);
	if (argc > 1)
	{
		if ((err = ft_parse_input(argc, argv, &data)))
			ft_print_error(err);
		if (!(game = ft_init_game()))
			return (0); //memory allocated error
		if (err == success)
		{
			ft_past_heroes(game, data);
			if ((err = ft_init_cursors(game)))
				ft_print_error(err);
			if (ft_battle(game))
				ft_print_arena(game);
			if (game->input->dump <= 0 ||
			game->input->dump >= game->total_cycles)
				ft_print_result(game);
			ft_game_over(&game);
		}
	}
	else
		ft_usage();
	return 0;
}

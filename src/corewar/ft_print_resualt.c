#include <corewar.h>
#include "ft_printf.h"

void ft_print_result(t_game *game)
{
	ft_set_color(white + game->winner->id);
	if (game->winner)
		ft_printf("! Congratulations to the winning player %d, "
			"weighting %d bytes, \"%s\" (\"%s\") !\n"RESET,
			  game->winner->id,
			  game->winner->header.prog_size,
			  game->winner->header.prog_name,
			  game->winner->header.comment);
}
#include "ft_printf.h"
#include "corewar.h"

void ft_logo()
{
	ft_printf("\n\t"E"93m █"E"57m█████"E"12m╗ ███"E"27m█"E"27m██"E"33m╗ "
	E"45m███"E"50m██"E"49m█"E"48m╗ "E"47m███"E"46m███"E"82m█╗█"E"118m█╗ "
	E"190m  "E"11m █"E"220m█╗ "E"214m███"E"208m██"E"202m╗ ████"E"196m██╗ \n\t"
	E"128m█"E"92m█"E"93m╔═"E"57m═══╝█"E"12m█╔═══"E"27m██╗"E"33m█"E"39m█"
	E"45m╔══"E"50m██"E"49m╗"E"48m██"E"47m╔══"E"46m══╝"E"82m██║   "E"190m █"
	E"11m█║"E"220m██╔"E"214m══█"E"208m█╗"E"202m██╔══█"E"196m█╗\n\t"E"126m█"
	E"127m█"E"128m║   "E"57m  ██║"E"12m   ██"E"27m║██"E"33m█"E"39m█"E"45m██╔"
	E"50m╝█"E"49m█"E"48m██"E"47m█╗ "E"46m ██"E"82m║ █"E"118m╗ "E"154m█"
	E"190m█║"E"11m██"E"220m███"E"214m██║"E"208m██"E"202m████╔╝\n\t"E"161m██"
	E"126m║     "E"57m██║  "E"12m ██║█"E"27m█╔═"E"33m═"E"39m█"E"45m█╗█"E"50m█╔"
	E"49m═"E"48m═╝"E"47m  █"E"46m█║█"E"82m██╗"E"118m██"E"154m║"E"190m██"
	E"11m╔═"E"220m═██"E"214m║██"E"208m╔═"E"202m═██╗\n\t"E"196m╚"E"161m███"
	E"126m█"E"127m█"E"128m█"E"92m╗"E"93m╚█"E"57m█████"E"12m╔╝██║"E"27m  █"
	E"33m█"E"39m║"E"45m███"E"50m██"E"49m█"E"48m█╗"E"47m╚██"E"46m█╔█"E"82m██╔"
	E"118m╝█"E"154m█"E"190m║ "E"11m █"E"220m█║█"E"214m█║ "E"208m █"
	E"202m█║\n\t"E"196m ╚═"E"161m═══"E"126m═"E"127m╝ "E"92m╚"E"93m══"
	E"57m═══╝ "E"12m╚═╝  "E"27m╚═╝"E"33m╚"E"39m═"E"45m═══"E"50m══"E"49m╝ "
	E"48m╚"E"47m══╝"E"46m╚══"E"82m╝ ╚"E"118m═╝ "E"190m ╚"E"11m═╝"E"220m╚═╝"
	E"214m  ╚"E"208m═╝\n\t"
			"%33s"E"118mVIRTUAL MACHINE v1.4\n\n"RESET,"");
}

void ft_usage()
{
	int i;

	i = -1;
	ft_logo();
	ft_printf(E"99mUsage:");
	ft_printf(" $>./corewar [OPTIONS]... [FILE]...\n\n");
	ft_printf("[FILE] extension must match <file name>.cor\n");
	ft_printf("[OPTIONS] mandatory arguments\n\n");
	while (++i < MAX_OPT)
		if(opt_tab[i].id)
			ft_printf("%6s %-12s %s\n\n", opt_tab[i].name,
					opt_tab[i].arg_format, opt_tab[i].comment);

}

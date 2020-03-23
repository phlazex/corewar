#include "ft_printf.h"

void ft_logo()
{
	ft_printf("\n"E"93m █"E"57m█████"E"12m╗ ███"E"27m█"E"27m██"E"33m╗ "
	E"45m███"E"50m██"E"49m█"E"48m╗ "E"47m███"E"46m███"E"82m█╗█"E"118m█╗ "
	E"190m  "E"11m █"E"220m█╗ "E"214m███"E"208m██"E"202m╗ ████"E"196m██╗ \n"
	E"128m█"E"92m█"E"93m╔═"E"57m═══╝█"E"12m█╔═══"E"27m██╗"E"33m█"E"39m█"
	E"45m╔══"E"50m██"E"49m╗"E"48m██"E"47m╔══"E"46m══╝"E"82m██║   "E"190m █"
	E"11m█║"E"220m██╔"E"214m══█"E"208m█╗"E"202m██╔══█"E"196m█╗\n"E"126m█"
	E"127m█"E"128m║   "E"57m  ██║"E"12m   ██"E"27m║██"E"33m█"E"39m█"E"45m██╔"
	E"50m╝█"E"49m█"E"48m██"E"47m█╗ "E"46m ██"E"82m║ █"E"118m╗ "E"154m█"
	E"190m█║"E"11m██"E"220m███"E"214m██║"E"208m██"E"202m████╔╝\n"E"161m██"
	E"126m║     "E"57m██║  "E"12m ██║█"E"27m█╔═"E"33m═"E"39m█"E"45m█╗█"E"50m█╔"
	E"49m═"E"48m═╝"E"47m  █"E"46m█║█"E"82m██╗"E"118m██"E"154m║"E"190m██"
	E"11m╔═"E"220m═██"E"214m║██"E"208m╔═"E"202m═██╗\n"E"196m╚"E"161m███"
	E"126m█"E"127m█"E"128m█"E"92m╗"E"93m╚█"E"57m█████"E"12m╔╝██║"E"27m  █"
	E"33m█"E"39m║"E"45m███"E"50m██"E"49m█"E"48m█╗"E"47m╚██"E"46m█╔█"E"82m██╔"
	E"118m╝█"E"154m█"E"190m║ "E"11m █"E"220m█║█"E"214m█║ "E"208m █"E"202m█║\n"
	E"196m ╚═"E"161m═══"E"126m═"E"127m╝ "E"92m╚"E"93m══"E"57m═══╝ "E"12m╚═╝  "
	E"27m╚═╝"E"33m╚"E"39m═"E"45m═══"E"50m══"E"49m╝ "E"48m╚"E"47m══╝"E"46m╚══"
	E"82m╝ ╚"E"118m═╝ "E"190m ╚"E"11m═╝"E"220m╚═╝"E"214m  ╚"E"208m═╝\n"
    "%38s"E"118mVIRTUAL MACHINE v1.2\n\n"RESET,"");
}

void ft_usage()
{
	ft_logo();
	ft_printf(E"99mUsage:\n");
	ft_printf(" $>./corewar [-options] <champions> <champions> ...\n\n");
	ft_printf(" options:\n");
	ft_printf("\t-v\tEnable visualisation\n"RESET);

}

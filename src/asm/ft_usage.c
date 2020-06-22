/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 20:17:15 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/22 20:17:17 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "corewar.h"

void	ft_logo(void)
{
	ft_printf("\n\t"E"93m █"E"57m█████"E"12m╗ ███"E"27m█"E"27m██"E"33m╗ "
		E"45m███"E"50m██"E"49m█"E"48m╗ "E"47m███"E"46m███"E"82m█╗█"E"118m█╗ "
		E"190m  "E"11m █"E"220m█╗ "E"214m███"E"208m██"E"202m╗ ████"
		E"196m██╗ \n\t"E"128m█"E"92m█"E"93m╔═"E"57m═══╝█"E"12m█╔═══"E"27m██╗"
		E"33m█"E"39m█"E"45m╔══"E"50m██"E"49m╗"E"48m██"E"47m╔══"E"46m══╝"
		E"82m██║   "E"190m █"E"11m█║"E"220m██╔"E"214m══█"E"208m█╗"E"202m██╔══█"
		E"196m█╗\n\t"E"126m█"E"127m█"E"128m║   "E"57m  ██║"E"12m   ██"E"27m║██"
		E"33m█"E"39m█"E"45m██╔"E"50m╝█"E"49m█"E"48m██"E"47m█╗ "E"46m ██"
		E"82m║ █"E"118m╗ "E"154m█"E"190m█║"E"11m██"E"220m███"E"214m██║"
		E"208m██"E"202m████╔╝\n\t"E"161m██"E"126m║     "E"57m██║  "E"12m ██║█"
		E"27m█╔═"E"33m═"E"39m█"E"45m█╗█"E"50m█╔"E"49m═"E"48m═╝"E"47m  █"
		E"46m█║█"E"82m██╗"E"118m██"E"154m║"E"190m██"E"11m╔═"E"220m═██"
		E"214m║██"E"208m╔═"E"202m═██╗\n\t"E"196m╚"E"161m███"E"126m█"E"127m█"
		E"128m█"E"92m╗"E"93m╚█"E"57m█████"E"12m╔╝██║"E"27m  █"E"33m█"E"39m║"
		E"45m███"E"50m██"E"49m█"E"48m█╗"E"47m╚██"E"46m█╔█"E"82m██╔"E"118m╝█"
		E"154m█"E"190m║ "E"11m █"E"220m█║█"E"214m█║ "E"208m █"E"202m█║\n\t"
		E"196m ╚═"E"161m═══"E"126m═"E"127m╝ "E"92m╚"E"93m══"E"57m═══╝ "
		E"12m╚═╝  "E"27m╚═╝"E"33m╚"E"39m═"E"45m═══"E"50m══"E"49m╝ "E"48m╚"
		E"47m══╝"E"46m╚══"E"82m╝ ╚"E"118m═╝ "E"190m ╚"E"11m═╝"E"220m╚═╝"
		E"214m  ╚"E"208m═╝\n\t%29s"E"118mASSEMBLER TRANSLATOR v 1.0\n\n"
		RESET, "");
}

void	ft_usage(void)
{
	ft_logo();
	ft_printf(E"99mUsage:");
	ft_printf(" $>./asm [OPTIONS]... [FILE]...\n\n");
	ft_printf("[FILE] extension must match <file name>.s or <file name>.cor\n");
	ft_printf("[OPTIONS] mandatory arguments\n\n");
	ft_printf("-asm - from assembler to bytecode\n");
	ft_printf("-dis - from bytecode to assembler\n");
}

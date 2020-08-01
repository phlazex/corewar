/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 20:17:15 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 13:37:04 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	ft_printf(" $>./asm [OPTION]... [FILE]...\n\n");
	ft_printf("A program for translating champion code"
			" written in assembly language into bytecode\n\n");
	ft_printf("[FILE] extension must match <file name>.s"
			" or <file name>.cor\n\n");
	ft_printf("[OPTION] mandatory arguments\n\n");
	ft_printf("    -asm  - to translate assembler files <filename>.s"
			" into bytecode\n\t    (file <filename>.cor will be created)\n\n");
	ft_printf("    -dis  - to convert the <filename>.cor bytecode back to an"
			" assembler file\n\t    (file <filename>.s will be created)\n\n");
	ft_printf("    -dout - to convert the <filename>.cor bytecode back to an"
			" assembler file\n\t    (detailed information will be displayed on"
			" the screen,\n\t    file <file name> .s will not be created)\n\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:31:36 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 13:32:11 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_exit(t_project *project, int exit_code, char *error_message)
{
	if (exit_code)
	{
		ft_get_error_message(project, exit_code, error_message);
	}
	ft_free(project);
	exit(exit_code);
}

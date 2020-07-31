/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 19:17:32 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/22 19:17:39 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_project	*ft_init_project(t_project *project)
{
	if (!(project = (t_project *)malloc(sizeof(t_project))))
		ft_exit(project, 2, NULL);
	ft_bzero(project, sizeof(*project));
	return (project);
}

int					main(int argc, char **argv)
{
	t_project	*project;

	ft_printf(CLR);
	project = ft_init_project(project);
	if (argc == 2)
		ft_dis_asm_route(project, NULL, argv[1]);
	else if (argc == 3)
		ft_dis_asm_route(project, argv[1], argv[2]);
	else
		ft_usage();
	ft_exit(project, 0, NULL);
	return (0);
}

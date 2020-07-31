/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 21:14:18 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/22 21:14:23 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_print_current_error_line_first(t_project *project)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((project->data->head)[i] != '\0')
	{
		if (j + 2 >= project->num_error_line - 1 &&
				j < project->num_error_line + 2)
		{
			ft_printf("\n%s%03zi%s\t", GRAY, j + 1, RESET);
			if (j == project->num_error_line - 1)
				ft_printf(RED);
			while ((project->data->head)[i] != '\0' &&
					(project->data->head)[i] != '\n')
				ft_printf("%c", (project->data->head)[i++]);
		}
		if ((project->data->head)[i] == '\n')
			j++;
		i++;
	}
}

static void	ft_print_current_error_line(t_project *project)
{
	size_t	i;

	i = 0;
	while (i < 42)
		ft_printf("%s-", CYAN, i++);
	ft_print_current_error_line_first(project);
	ft_printf("\n");
	i = 0;
	while (i < 42)
		ft_printf("%s_", CYAN, i++);
	ft_printf("\n");
}

void		ft_get_error_message(
		t_project *project, int exit_code, char *error_message)
{
	if (exit_code == 1)
		ft_printf("Error: Could not open file %s\n", project->file_name);
	else if (exit_code == 2)
		ft_printf("Error: Failed to allocate memory\n");
	else if (exit_code == 3)
		ft_printf("Error: Unknown error\n");
	else if (exit_code == 4)
	{
		ft_printf("Error: Expected token \"%s\" on line %zi not found\n",
				error_message, project->num_error_line);
		ft_print_current_error_line(project);
	}
	else if (exit_code == 5)
		ft_printf("Error: Invalid token length \"%s\"\n", error_message);
	else if (exit_code == 6)
		ft_printf("Error: The expected tokens \"%s\" and \"%s\" are missing\n",
				NAME_CMD_STRING, COMMENT_CMD_STRING);
	else if (exit_code == 7)
	{
		ft_printf("Error: Invalid line %zi:\n",
				project->num_error_line);
		ft_print_current_error_line(project);
		if (project->code_error)
		{
			ft_printf("%s%s\n", YELLOW, project->code_error);
		}
	}
}

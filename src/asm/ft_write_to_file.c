/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_to_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:18:43 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 13:21:07 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_get_file_name(char *file)
{
	char	*ptr;
	char	*new_file;

	if ((ptr = ft_strstr(file, ".s")))
	{
		new_file = ft_strsub(file, 0, ptr - file);
//		new_file = ft_strjoin_free_first(&new_file, ".cor_new");
		new_file = ft_strjoin_free_first(&new_file, ".cor");
		return (new_file);
	}
	return (NULL);
}

int			ft_write_to_file(t_project *project, char *file)
{
	int		fd;
	size_t	length;
	char	*new_file;

	new_file = NULL;
	if ((new_file = ft_get_file_name(file)))
	{
		if ((fd = open(new_file, O_WRONLY | O_TRUNC | O_CREAT, 0666)) <= 0)
			return (1);
	}
	else
		return (1);
	length = (size_t)(sizeof(int) * 4 + COMMENT_LENGTH +
			PROG_NAME_LENGTH + project->size_program);
	write(fd, project->program, length);
	close(fd);
	ft_printf("Writing output program to %s\n", new_file);
	ft_strdel(&new_file);
	ft_free(project);
	return (0);
}

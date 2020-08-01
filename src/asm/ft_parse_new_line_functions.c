/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_new_line_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 19:14:00 by mfahey            #+#    #+#             */
/*   Updated: 2020/07/02 19:15:49 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_new_word_without_space(char *word, size_t length)
{
	size_t	i;
	size_t	j;
	char	*new_word;

	if (!(new_word = ft_strnew(length + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (word[i] != '\0')
	{
		if (!ft_isspace(word[i]))
			new_word[j++] = word[i];
		i++;
	}
	new_word[j] = '\0';
	ft_strdel(&word);
	return (new_word);
}

static char	*ft_word_without_space(char *word)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (word[i] != '\0')
		if (!ft_isspace(word[i++]))
			j++;
	if (i == j)
		return (word);
	return (ft_new_word_without_space(word, j));
}

static char	*ft_validation_label_name(
		t_prog_list *prog_list, size_t i, size_t j)
{
	char	*str;

	if ((prog_list->new_line)[i - 1] == LABEL_CHAR)
	{
		str = ft_strsub(prog_list->new_line, i - j, j - 1);
		if (ft_is_label_command(str, 0))
			return (str);
	}
	else if (ft_isalpha((prog_list->new_line)[i - 1]))
	{
		str = ft_strsub(prog_list->new_line, i - j, j);
		if (ft_is_label_command(str, 26))
			return (str);
	}
	return (NULL);
}

static int	ft_get_new_word_else(t_prog_list *prog_list, size_t i, size_t j)
{
	char	*word;

	if ((word = ft_strsub(prog_list->new_line, i - j, j)))
		;
	if (!prog_list->args[0])
		prog_list->args[0] = ft_word_without_space(word);
	else if (!prog_list->args[1])
		prog_list->args[1] = ft_word_without_space(word);
	else if (!prog_list->args[2])
		prog_list->args[2] = ft_word_without_space(word);
	else if (prog_list->args[0] && prog_list->args[1] && prog_list->args[2])
		return (1);
	return (0);
}

int			ft_get_new_word(t_prog_list *prog_list, size_t i, size_t j)
{
	char	*word;

	word = NULL;
	if (!prog_list->command)
	{
		if (!(word = ft_validation_label_name(prog_list, i, j)))
			return (1);
		if ((prog_list->new_line)[i - 1] == LABEL_CHAR &&
				!prog_list->label && word)
			prog_list->label = word;
		else if (!prog_list->command && word)
			prog_list->command = word;
		else
			return (1);
	}
	else
	{
		if (ft_get_new_word_else(prog_list, i, j))
			return (1);
	}
	return (0);
}

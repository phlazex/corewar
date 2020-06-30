/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_new_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:22:21 by mfahey            #+#    #+#             */
/*   Updated: 2020/06/30 15:25:56 by mfahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*ft_new_word_without_space(char *word, size_t length)
{
	size_t	i;
	size_t	j;
	char	*new_word;

	if (!(new_word = ft_strnew(length + 1)))
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	while (word[i] != '\0')
	{
		if (!ft_isspace(word[i]))
		{
			new_word[j++] = word[i];
		}
		i++;
	}
	new_word[j] = '\0';
	ft_strdel(&word);
//	ft_printf("i!=j|i=%zi|j=%zi|w=%s|", i, j, new_word);
	return (new_word);
}

static char 	*ft_word_without_space(char *word)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (word[i] != '\0')
	{
		if (!ft_isspace(word[i++]))
		{
			j++;
		}
	}
//	ft_printf("w=%s|", word);
	if (i == j)
	{
//		ft_printf("i==j|i=%zi|w=%s|", i, word);
		return (word);
	}
	return (ft_new_word_without_space(word, j));
}

static char			*ft_validation_label_name(t_prog_list *prog_list, size_t i, size_t j)
{
	char 	*str;

//	ft_printf("%s|\n", prog_list->new_line + i);
	if ((prog_list->new_line)[i - 1] == LABEL_CHAR)
	{
		str = ft_strsub(prog_list->new_line, i - j, j - 1);
		if (ft_is_label_command(str, 0))
		{
			return (str);
		}
	}
	else if (ft_isalpha((prog_list->new_line)[i - 1]))
	{
		str = ft_strsub(prog_list->new_line, i - j, j);
		if (ft_is_label_command(str, 26))
		{
			return (str);
		}
	}
	return (NULL);
}

static int 		ft_get_new_word(t_prog_list *prog_list, size_t i, size_t j)
{
	char	*word;

	word = NULL;
	if (!prog_list->command)
	{
		if (!(word = ft_validation_label_name(prog_list, i, j)))
		{
//			ft_printf("%s|", word ? word : "(null)");
//			ft_printf("ERROR2|"); //Не корректная строка
			return (1);
		}
		if ((prog_list->new_line)[i - 1] == LABEL_CHAR && !prog_list->label && word)
		{
			prog_list->label = word;
		}
		else if (!prog_list->command && word)
		{
			prog_list->command = word;
//			ft_printf("%s|%zi|%zi|\n", prog_list->new_line, i, j);
		}
		else
		{
//			ft_printf("ERROR3|"); //Не корректная строка
			return (1);
		}
	}
	else
	{
//		ft_printf("%s", prog_list->new_line + i);
		if ((word = ft_strsub(prog_list->new_line, i - j, j)))
		{
//			ft_printf("|%s|", ft_strsub(prog_list->new_line, i - j, j));
		}
		if (!prog_list->args[0])
		{
			prog_list->args[0] = ft_word_without_space(word);
		}
		else if (!prog_list->args[1])
		{
			prog_list->args[1] = ft_word_without_space(word);
		}
		else if (!prog_list->args[2])
		{
			prog_list->args[2] = ft_word_without_space(word);
		}
		else if (prog_list->args[0] && prog_list->args[1] && prog_list->args[2])
		{
			ft_printf("ERROR4|"); //Не верное количество аргуметов команды
			return (1);
		}
	}
	return (0);
}

int			ft_parse_new_line(t_prog_list *prog_list)
{
	size_t	i;
	size_t	j;

	prog_list->label = NULL;
	prog_list->command = NULL;
	prog_list->args[0] = NULL;
	prog_list->args[1] = NULL;
	prog_list->args[2] = NULL;
	prog_list->command_size = 0;
	prog_list->command_num = 0;
	prog_list->arg_label_list_ptr[0] = NULL;
	prog_list->arg_label_list_ptr[1] = NULL;
	prog_list->arg_label_list_ptr[2] = NULL;
	prog_list->args_code[0] = 0;
	prog_list->args_code[1] = 0;
	prog_list->args_code[2] = 0;
	i = 0;
//	ft_printf("%s|\n", prog_list->new_line);
	while ((prog_list->new_line)[i] != '\0')
	{
		if (!prog_list->command)
		{
			j = 0;
			while ((prog_list->new_line)[i] != '\0' && ft_is_labels_char((prog_list->new_line)[i], 0))
			{
//				ft_printf("\n%c|%zi|%zi|", (prog_list->new_line)[i], i, j);
				j++;
				i++;
			}
			if ((prog_list->new_line)[i] == LABEL_CHAR && !prog_list->label && !prog_list->command)
			{
				j++;
				i++;
			}
			if (ft_get_new_word(prog_list, i, j))
			{
				return (1);
			}
			while ((prog_list->new_line)[i] != '\0' && ft_isspace((prog_list->new_line)[i]))
			{
				i++;
			}
		}
		else
		{
			j = 0;
			while ((prog_list->new_line)[i] != '\0' && (prog_list->new_line)[i] != SEPARATOR_CHAR)
			{
//				ft_printf("\n%c|%zi|%zi|", (prog_list->new_line)[i], i, j);
				j++;
				i++;
			}
			if (ft_get_new_word(prog_list, i, j))
			{
				return (1);
			}
			if ((prog_list->new_line)[i] == SEPARATOR_CHAR)
			{
				i++;
			}
		}
	}
	return (0);
}

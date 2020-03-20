
#include <corewar.h>
#include <ft_printf.h>

#include <fcntl.h>
#include <zconf.h>
#include "libft.h"

static int ft_is_option(char *string)
{
	return 0;
}

static int ft_is_hero(char *string)
{
	return 0;
}

static t_err ft_get_hero(t_hero *hero)
{
	t_mem *mem;
	t_err err;
	int fd;

	err = success;
	if ((fd = open(hero->file_name, O_RDONLY)) <= 0)
		return (no_file);
	if (!(mem = ft_init_memory()))
		return (no_memory);
	if (fast_read_in_memory(fd, mem) == -1)
		err = w_file_read;
	if (!err)
		err = ft_parse_hero(hero, mem);
	ft_memdel((void**)&mem->head);
	ft_memdel((void**)&mem);
	close(fd);
	return (err);
}

static t_err ft_get_heroes(t_data *data)
{
	int i;
	int err;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (data->hero_list[i].id)
			if ((err = ft_get_hero(data->hero_list + i)))
				return (err);
		++i;
	}
	return (success);
}

static t_err ft_check_file_name(char *file_name)
{
	size_t len;

	len = ft_strlen(file_name);
	if (len < 3)
		return (w_file_name);
	if (*(int32_t*)(file_name + len - 4) == 0x726f632e) // 0x726f632e == "./cor"
		return (success);
	return (w_format);
}

static t_err ft_get_heroes_files(int argc, char **argv, t_data *data)
{
	t_err err;
	int i;
	int j;
	int index;
	i = 0;
	while(++i < argc)
	{
		if (!ft_strcmp(argv[i], "-n"))
		{
			index = ft_atoi(argv[++i]);
			if (data->hero_list[index - 1].id)
				return (dup_id);
			data->hero_list[index - 1].id = index;
			data->hero_list[index - 1].file_name = argv[++i];
		}
	}
	i = 0;
	while(++i < argc)
	{
		if (!ft_strcmp(argv[i], "-n"))
			i += 2;
		else if (!ft_check_file_name(argv[i]))
		{
			j = -1;
			while (++j < MAX_PLAYERS)
				if (data->hero_list[j].id == 0)
				{
					data->hero_list[j].id = j + 1;
					data->hero_list[j].file_name = argv[i];
					break;
				}
			if (j == MAX_PLAYERS)
				return (w_player_number);
		}
	}
	return (success);
}


t_err ft_is_correct_number(const char *number)
{
	if (number == NULL || *number == 0 || *(number + 1))
		return (w_player_number);
	if (*number == '1' || *number == '2' || *number == '3' || *number == '4')
		return (success);
	return (w_player_number);
}

static t_err ft_check_format(int argc, char **argv)
{
	t_err err;
	int i;

	i = 0;
	if (!argv)
		return (w_format);
	while(++i < argc)
	{
		if (!argv[i] || !argv[i][0])
			return (w_format);
		if (!ft_strcmp(argv[i], "-n"))
		{
			if (++i < argc && !(err = ft_is_correct_number(argv[i])))
			{
				if (++i >= argc || (err = ft_check_file_name(argv[i])))
					return (err);
			} else
				return (err);
		}
		if (!ft_strcmp(argv[i], "-dump"))
			if (!(++i < argc && ft_atoi(argv[i]) <= 0))
				return (w_format);
		if (i > argc)
			return (w_format);
		if ((err = ft_check_file_name(argv[i])))
			return (w_file_name);
	}
	return (success);
}


t_err ft_parse_input(int argc, char **argv, t_data **data)
{
	t_err err;

	*data = NULL;
	if ((err = ft_check_format(argc, argv)))
		return (err);
	if (!(*data = (t_data*)malloc(sizeof(**data))))
		return (no_memory);
	ft_bzero(*data, sizeof(**data));
	if ((err = ft_get_heroes_files(argc, argv, *data)))
		return (err);
	if ((err = ft_get_heroes(*data)))
		return (err);
	return (success);
}
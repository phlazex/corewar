
#include <corewar.h>
#include <ft_printf.h>

static int ft_is_option(char *string)
{
	return 0;
}

static int ft_is_hero(char *string)
{
	return 0;
}

static t_hero *ft_get_hero(char *string)
{
	return (NULL);
}
static t_err ft_add_hero(t_data *data, char *file_name)
{
	return (success);
}

static t_err ft_validate_input(int argc, char **argv, t_data *data)
{
	t_err err;
	int i;

	i = 0;
	while(++i < argc)
	{
		if (!(err = ft_is_option(argv[i])))
			data->flags = 1;
		else if (!(err = ft_is_hero(argv[i])))
		{
			if (!(err = ft_add_hero(data, argv[i])))
				return (err);
		}
		else
			return (err); //wrong input TODO add clear mem
	}
	return (success);
}
static t_err ft_check_file_name(char *file_name)
{
	size_t len;

	len = ft_strlen(file_name);
	if (len < 3)
		return (w_file_name);
	if (*(int32_t*)(file_name + len - 4) != 0x726f632e)
	{
		ft_printf("%x\n", *(int32_t*)(file_name + len - 4));
		return (w_file_name);
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
			if (++i < argc && (err = ft_is_correct_number(argv[i])))
			{
				if (++i < argc && (err = ft_check_file_name(argv[i])))
					return (err);
			} else
				return (err);
		}
		if (!ft_strcmp(argv[i], "-dump"))
			if (!(++i < argc && ft_atoi(argv[i]) >0))
				return (w_format);
		if (i >= argc)
			return (w_format);
		if ((err = ft_check_file_name(argv[i])))
			return (w_file_name);
	}
	return (success);
}


t_err ft_analyse_input(int argc, char **argv, t_data **data)
{
	t_err err;
	if ((err = ft_check_format(argc, argv)))
		return (err);
//	if (!(*data = (t_data*)malloc(sizeof(**data))))
//		return (no_memory);
//	if (!(err = ft_validate_input(argc, argv, *data)))
//		return (err); //incorrect data


}
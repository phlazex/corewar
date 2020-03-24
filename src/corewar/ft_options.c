#include "corewar.h"
#include "libft.h"

t_err ft_flag_n(int32_t argc, int32_t *current, char **argv, t_data *data)
{
	t_err err;

	err = success;
	if (++(*current) < argc && !(err = ft_is_correct_number(argv[(*current)])))
		if (++(*current) >= argc || (err = ft_check_file_name(argv[(*current)])))
			return (err);
	return (err);
}

t_err ft_flag_dump(int32_t argc, int32_t *current, char **argv, t_data *data)
{
	if (!(++(*current) < argc && (data->dump = ft_atoi(argv[*current])) < 0))
		return (w_format);
	++(*current);
	return success;
}

t_err ft_flag_q(int32_t argc, int32_t *current, char **argv, t_data *data)
{
	data->quiet = true;
	++(*current);
	return success;
}

//t_err ft_flag_dump()
//{
//	return success;
//}t_err ft_flag_dump()
//{
//	return success;
//}



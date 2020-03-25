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
	if (++(*current) < argc && (data->dump = ft_atoi(argv[*current])) >= 0)
		return success;
	return (w_format);
}

t_err ft_flag_q(int32_t argc, int32_t *current, char **argv, t_data *data)
{
	data->quiet = true;
	return success;
}
t_err ft_flag_a(int32_t argc, int32_t *current, char **argv, t_data *data)
{
	data->enable_aff = true;
	return success;
}

//t_err ft_flag_dump()
//{
//	return success;
//}t_err ft_flag_dump()
//{
//	return success;
//}



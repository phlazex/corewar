//
// Created by xel on 13.03.2020.
//

#ifndef ASM_H
# define ASM_H

# define UNKNOWN_INSTRUCTION "Unknown instruction"
# define WRONG_ARGUMENT_NUMBER "Wrong argument number for an instruction"
# define WRONG_ARGUMENT_TYPE "Wrong argument type or value for an instruction"
# define WRONG_CHARACTER "Wrong string"

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "corewar.h"
# include "corewar_op.h"
# include <ft_printf.h>

typedef struct	s_prog_list
{
	char 					*line_ptr;
	char 					*endl_ptr;
	char					*new_line;
	char					*label;
	char					*command;
	char 					*args[3];
	struct s_prog_list		*prev_list;
	struct s_prog_list		*next_list;
	size_t					command_num;
	size_t					command_size;
	struct s_prog_list		*arg_label_list_ptr[3];
	size_t					args_code[3];
	char					*code_line;
	size_t 					num_line;
}				t_prog_list;

typedef struct s_project
{
	t_mem					*data;
	t_prog_list				*prog_list;
	t_prog_list				*current_list;
	char 					*name;
	int						size_program;
	char 					*prog_size;
	char 					*comment;
	char					*program;
	char					*current;
	char					*end;
	size_t 					num_current_line;
	char					*code_error;
	size_t					num_error_line;
	char					*file_name;
	int						option;
	int						route;
	int						fd;
	char					*new_file;
}				t_project;

int			ft_project_init(t_project *project, int (*ft_parse)(t_mem *, t_project *));
void		ft_usage();
int			ft_disassemble(t_project *project);
int			ft_parse_file_dis(t_mem *mem, t_project *project);
int			ft_parse_file(t_mem *mem, t_project *project);
void		ft_exit(t_project *project, int exit_code, char *error_message);
void		ft_free(t_project *project);
void		ft_free_mem(t_mem *data);
void		ft_get_error_message(t_project *project, int exit_code, char *error_message);
int			ft_write_to_file(t_project *project);
void		ft_parse_current(t_project *project);
int			ft_isspace(int chr);
int			ft_is_label_command(char *str, size_t length);
int			ft_is_labels_char(int chr, size_t length);
char		*ft_get_str(t_project *project, char *str);
char		*ft_get_chr(t_project *project, int chr);
char		*ft_get_data_cmd(char *start, char *end);
int			ft_is_valid_line(t_project *project, char *comment);
int			ft_get_name_comment(t_project *project, char *data_cmd, char *comment, char *cmd_name);
int			ft_is_zero_line(t_project *project, char *comment);
t_prog_list	*ft_init_prog_list(t_project *project, char *comment);
int			ft_parse_new_line(t_prog_list *prog_list);
int			ft_check_prog_list(t_project *project);
int			ft_get_program_line(t_project *project);
int			ft_check_args(t_project *project);
int			ft_is_reg(t_project *project, size_t arg_num);
int			ft_is_dir(t_project *project, size_t arg_num);
int			ft_is_ind(t_project *project, size_t arg_num);
int			ft_check_count_args(t_project *project);
void		ft_get_args(t_project *project, size_t *i);
void		ft_get_two_bytes(char *str, size_t *i, int num);
void		ft_get_four_bytes(char *str, size_t *i, int num);
int			ft_get_prev_num_label(t_project *project, size_t arg_num);
int			ft_get_next_num_label(t_project *project, size_t arg_num);
int			ft_is_valid_label(t_project *project, char *label, size_t arg_num);
int			ft_is_arg_func(t_project *project, size_t arg_num, size_t command_size, size_t arg_code);
int			ft_is_ind_dir_func(t_project *project, size_t arg_num, size_t i);
int			ft_get_new_word(t_prog_list *prog_list, size_t i, size_t j);
int			ft_open_file_for_write(t_project *project);

#endif

//
// Created by xel on 13.03.2020.
//

#ifndef ASM_H
#define ASM_H

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "corewar.h"
#include "corewar_op.h"
#include <ft_printf.h>

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
	size_t					num_error;
	size_t					num_error_line;
}				t_project;

int			ft_project_init(char *file_name, t_project **project, int (*ft_parse)(t_mem *, t_project *, char *));
void		ft_usage();
int			ft_disassemble(t_project *project);
int			ft_parse_file_dis(t_mem *mem, t_project *project, char *file);
int			ft_parse_file(t_mem *mem, t_project *project, char *file);
void		ft_exit(t_project *project, int exit_code, char *error_message);
void		ft_free(t_project *project);
void		ft_free_mem(t_mem *data);
void		ft_get_error_message(t_project *project, int exit_code, char *error_message);
int			ft_write_to_file(t_project *project, char *file);
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

#endif

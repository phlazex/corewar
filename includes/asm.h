//
// Created by xel on 13.03.2020.
//

#ifndef ASM_H
#define ASM_H

#include "libft.h"

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

int		ft_project_init(char *file_name, t_project **project, int (*ft_parse)(t_mem *, t_project *, char *));
void	ft_usage();
int		ft_disassemble(t_project *project);
int		ft_parse_file_dis(t_mem *mem, t_project *project, char *file);
int		ft_parse_file(t_mem *mem, t_project *project, char *file);
void	ft_exit(t_project *project, int exit_code, char *error_message);

#endif

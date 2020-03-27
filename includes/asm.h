//
// Created by xel on 13.03.2020.
//

#ifndef ASM_H
#define ASM_H

#include "libft.h"


typedef struct s_project
{
	t_mem		*data;
	char 		*name;
	char 		*prog_size;
	char 		*comment;
	char		*program;
	char		*current;
	char		*end;
}				t_project;

int ft_project_init(char *file_name, t_project **project);
void ft_usage();
int ft_disassemble(t_project *project);

#endif

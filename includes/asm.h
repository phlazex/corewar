//
// Created by xel on 13.03.2020.
//

#ifndef ASM_H
#define ASM_H

#include "libft.h"

//typedef struct s_data
//{
//	char		*file_name;
//
//}				t_data;

typedef struct s_project
{
	t_mem		*data;
	char 		*name;
	char 		*prog_size;
	char 		*comment;
	char		*program;
	char		*end;
}				t_project;

int ft_project_init(char *file_name, t_project **project);
void ft_usage();
char  *ft_disassemble(char *program);

#endif

cmake_minimum_required(VERSION 3.15)
project(corewar C)

set(CMAKE_C_STANDARD 99)

add_executable(corewar main.c)


include_directories(
        includes
        lib/libft/includes
        lib/ft_printf/includes
)

add_subdirectory(lib/libft)
add_subdirectory(lib/ft_printf)

target_link_libraries(corewar libft libftprintf)
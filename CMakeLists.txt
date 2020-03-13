cmake_minimum_required(VERSION 3.15)
project(corewar C)

set(CMAKE_C_STANDARD 99)
set(COREWAR_SRC
        src/corewar/corewar.c
        )
set(ASM_SRC
        src/asm/asm.c
        )

add_executable(corewar ${COREWAR_SRC} includes/corewar.h)
add_executable(asm ${ASM_SRC} includes/asm.h)


include_directories(
        includes
        lib/libft/includes
        lib/ft_printf/includes
)

add_subdirectory(lib/libft)
add_subdirectory(lib/ft_printf)

target_link_libraries(corewar libft libftprintf)
target_link_libraries(asm libft libftprintf)
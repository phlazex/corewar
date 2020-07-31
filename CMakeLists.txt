cmake_minimum_required(VERSION 3.10)
project(corewar C)

set(CMAKE_C_STANDARD 99)
set(COREWAR_SRC

        src/corewar/ft_usage.c
        src/corewar/ft_print_error.c
        src/corewar/ft_init_game.c
        src/corewar/ft_game_orver.c
        src/corewar/ft_print_arena.c
        src/corewar/ft_parse_input.c
        src/corewar/ft_parse_hero.c
        src/corewar/ft_past_heroes.c
        src/corewar/ft_init_cursors.c
        src/corewar/ft_battle.c
        src/corewar/ft_doomsday.c
        src/corewar/ft_execute.c
        src/corewar/ft_options_2.c
        src/corewar/ft_get_heroes.c
        src/corewar/ft_check_opt.c
        src/corewar/ft_get_heroes_file.c
        src/corewar/ft_print_resualt.c
        src/corewar/ft_atoin.c
        src/corewar/ft_new_cursor.c
        src/corewar/ft_get_op.c
        src/corewar/op/op_live.c
        src/corewar/op/op_add.c
        src/corewar/op/op_ld.c
        src/corewar/op/utils.c
        src/corewar/op/op_st.c
        src/corewar/op/op_zjmp.c
        src/corewar/op/op_sti.c
        src/corewar/op/op_fork.c
        src/corewar/op/op_sub.c
        src/corewar/op/op_and.c
        src/corewar/op/op_or.c
        src/corewar/ft_print_arena_utils.c
        src/corewar/ft_past_reg.c
        src/corewar/op/op_xor.c src/corewar/op/op_ldi.c src/corewar/op/op_lld.c src/corewar/op/op_lldi.c src/corewar/op/op_lfork.c src/corewar/op/op_aff.c src/corewar/ft_options.c)

set(LOGER_SRC
        src/logger/logger.c)
set(ASM_SRC
        src/asm/asm.c
        src/asm/ft_usage.c
        src/asm/ft_disassemble.c
        src/asm/ft_project_init.c
        src/asm/ft_free_mem.c
        src/asm/ft_print_error.c
        src/asm/ft_write_to_file.c
        src/asm/ft_exit.c
        src/asm/ft_parse_file.c
        src/asm/ft_parse_current_line.c
        src/asm/ft_libc_functions.c
        src/asm/ft_parse_functions.c
        src/asm/ft_parse_current_line_getters.c
        src/asm/ft_init_prog_list.c
        src/asm/ft_parse_new_line.c
        src/asm/ft_check_prog_list.c
        src/asm/ft_prog_list_getters.c
        src/asm/ft_check_prog_list_args.c
        src/asm/ft_check_prog_list_args_type.c
        src/asm/ft_prog_list_getters_args.c
        src/asm/ft_prog_list_getters_line_data.c
        src/asm/ft_check_prog_list_args_type_functions.c
        src/asm/ft_parse_new_line_functions.c
        src/asm/ft_route.c
        src/corewar/ft_atoin.c
        src/corewar/ft_new_cursor.c
        src/corewar/ft_print_arena.c
        src/corewar/op/op_live.c
        src/corewar/op/op_add.c
        src/corewar/op/op_ld.c
        src/corewar/op/utils.c
        src/corewar/op/op_st.c
        src/corewar/op/op_zjmp.c
        src/corewar/op/op_sti.c
        src/corewar/op/op_fork.c
        src/corewar/op/op_sub.c
        src/corewar/op/op_and.c
        src/corewar/op/op_or.c
        src/corewar/op/op_xor.c
        src/corewar/op/op_ldi.c
        src/corewar/op/op_lld.c
        src/corewar/op/op_lldi.c
        src/corewar/op/op_lfork.c
        src/corewar/op/op_aff.c
        src/corewar/ft_past_reg.c
        src/corewar/ft_print_arena_utils.c)

set (VIS_SRC
        src/vis/ft_delete_window.c
        src/vis/ft_draw_line.c
        src/vis/ft_draw_rectangle.c
        src/vis/ft_init_window.c
        src/vis/ft_close_window.c
        src/vis/ft_key_press.c
        src/vis/ft_put_logo.c
        src/vis/ft_draw_grid.c
        src/vis/ft_get_color.c
        src/vis/ft_draw_champions.c
        src/vis/ft_redraw_game_filed.c
        src/vis/ft_rewrite_point.c
        src/vis/ft_draw_circle.c
        src/vis/ft_put_info.c
        src/vis/ft_check_color.c
        src/vis/ft_draw_heart.c
        src/vis/ft_check_lives.c
        src/vis/ft_draw_start_field.c
        src/vis/ft_draw_game_field.c
        )

add_executable(corewar ${COREWAR_SRC} ${LOGER_SRC} ${VIS_SRC} includes/corewar.h includes/op.h src/corewar/corewar.c includes/corewar_op.h)
add_executable(asm ${ASM_SRC} includes/corewar.h includes/asm.h)
add_executable(sandbox ${COREWAR_SRC} ${LOGER_SRC} includes/corewar.h includes/op.h)

include_directories(
        includes
        lib/libft/includes
        lib/ft_printf/includes
        minilibx/
)

add_subdirectory(lib/libft)
add_subdirectory(lib/ft_printf)

target_link_libraries(corewar libft libftprintf ${PROJECT_SOURCE_DIR}/minilibx/libmlx.a "-framework OpenGL -framework AppKit")
target_link_libraries(asm libft libftprintf)
target_link_libraries(sandbox libft libftprintf)
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:50:21 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/16 16:53:42 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

char	**create_board(t_vector2 size)
{
	char		**result;
	t_vector2	cursor;

	cursor = vec2(0, 0);
	result = malloc(sizeof(char *) * (size.y + 1));
	result[size.y] = 0;
	while (cursor.y < size.y)
	{
		cursor.x = 0;
		result[cursor.y] = malloc(sizeof(char) * (size.x + 1));
		while (cursor.x < size.x)
		{
			result[cursor.y][cursor.x] = '0';
			cursor.x++;
		}
		result[cursor.y][cursor.x] = 0;
		cursor.y++;
	}
	return (result);
}

t_mlx	*editor_window(t_vector2 board_size)
{
	t_mlx		*mlx;

	mlx = setup_mlx("EDIT MAP", vec2(1500, 900));
	mlx->board_size = board_size;
	mlx->is_clicking = FALSE;
	mlx->board = create_board(mlx->board_size);
	new_image(mlx, mlx->screen_size, vec2(0, 0));
	draw_board(mlx, 0xFFFFFF, mlx->board, mlx->board_size);
	add_obj_to_list(&mlx->obj_list, obj_set_on_click(create_obj(BUTTON,
				vec2(1750, 450), 0xFFFFFF, "SUBMIT"),
			mlx_loop_end_signal, mlx));
	mlx_hook(mlx->win, ON_DESTROY, 0, fun_exit, mlx->mlx);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_hook(mlx->win, ON_MOUSEMOVE, 1L << 6, _input_mouse_board, mlx);
	mlx_hook(mlx->win, ON_MOUSEDOWN, 1L << 2, _input_mouse_click_down, mlx);
	mlx_hook(mlx->win, ON_MOUSEUP, 1L << 3, _input_mouse_click_up, mlx);
	mlx_loop(mlx->mlx);
	return (mlx);
}

void	map_size_obj(t_mlx *mlx, t_object *value_x, t_object *value_y)
{
	add_obj_to_list(&mlx->obj_list, obj_set_on_click(create_obj(BUTTON,
				vec2(50, 65), 0xFFFFFF, ""), modif_label_up, value_x));
	add_obj_to_list(&mlx->obj_list, create_obj(LABEL, vec2(50, 100), 0xFFFFFF,
			"X VALUE"));
	add_obj_to_list(&mlx->obj_list, obj_set_on_click(create_obj(BUTTON,
				vec2(50, 120), 0xFFFFFF, ""), modif_label_down, value_x));
	add_obj_to_list(&mlx->obj_list, obj_set_on_click(create_obj(BUTTON,
				vec2(100, 65), 0xFFFFFF, ""), modif_label_up, value_y));
	add_obj_to_list(&mlx->obj_list, create_obj(LABEL, vec2(100, 100), 0xFFFFFF,
			"Y VALUE"));
	add_obj_to_list(&mlx->obj_list, obj_set_on_click(create_obj(BUTTON,
				vec2(100, 120), 0xFFFFFF, ""), modif_label_down, value_y));
	add_obj_to_list(&mlx->obj_list, obj_set_on_click(create_obj(BUTTON,
				vec2(150, 100), 0xFFFFFF, "CREATE"),
			mlx_loop_end_signal, mlx));
	add_obj_to_list(&mlx->obj_list, value_x);
	add_obj_to_list(&mlx->obj_list, value_y);
}

t_vector2	map_size_window(void)
{
	t_mlx		*mlx;
	t_vector2	board_size;
	t_object	*value_x;
	t_object	*value_y;

	value_x = obj_set_val_size(create_obj(LABEL,
				vec2(50, 110), 0xFFFFFF, "10"), 10, vec2(25, 25));
	value_y = obj_set_val_size(create_obj(LABEL,
				vec2(100, 110), 0xFFFFFF, "10"), 10, vec2(25, 25));
	mlx = setup_mlx("SELECT SIZE", vec2(0, 0));
	map_size_obj(mlx, value_x, value_y);
	new_image(mlx, vec2(300, 300), vec2(0, 0));
	draw_object_list(mlx, mlx->obj_list);
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, fun_exit, mlx->mlx);
	mlx_hook(mlx->win, ON_MOUSEDOWN, 1L << 2, _input_mouse_click_down_ex, mlx);
	mlx_hook(mlx->win, ON_MOUSEUP, 1L << 3, _input_mouse_click_up_ex, mlx);
	mlx_hook(mlx->win, ON_MOUSEMOVE, 1L << 6, _input_mouse_ex, mlx);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	mlx_loop(mlx->mlx);
	board_size = vec2(value_x->value, value_y->value);
	free_mlx(mlx);
	return (board_size);
}

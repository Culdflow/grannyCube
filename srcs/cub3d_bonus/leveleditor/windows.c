/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:50:21 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/01 18:36:12 by dfeve            ###   ########.fr       */
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
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, mlx_loop_end_signal, 5, vec2(1750, 450), vec2(50, 25), 0xFFFFFF, "SUBMIT", mlx));
	mlx_hook(mlx->win, ON_DESTROY, 0, fun_exit, mlx->mlx);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_hook(mlx->win, ON_MOUSEMOVE,1L << 6, _input_mouse_board, mlx);
	mlx_hook(mlx->win, ON_MOUSEDOWN, 1L << 2, _input_mouse_click_down, mlx);
	mlx_hook(mlx->win, ON_MOUSEUP, 1L << 3, _input_mouse_click_up, mlx);
	mlx_loop(mlx->mlx);
	return(mlx);
}

void	map_size_obj(t_mlx *mlx, t_object *label_x, t_object *label_y, t_object *slider)
{
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_up, 1
						, vec2(50, 65), vec2(25, 15), 0xFFFFFF, "", label_x));
	add_obj_to_list(&mlx->obj_list, label_x);
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_down, 2
						, vec2(50, 120), vec2(25, 15), 0xFFFFFF, "", label_x));
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_up, 3
						, vec2(100, 65), vec2(25, 15), 0xFFFFFF, "", label_y));
	add_obj_to_list(&mlx->obj_list, label_y);
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_down, 4
						, vec2(100, 120), vec2(25, 15), 0xFFFFFF, "", label_y));
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, mlx_loop_end_signal, 5
						, vec2(150, 90), vec2(25, 15), 0xFFFFFF, "CREATE", mlx));
	add_obj_to_list(&mlx->obj_list, slider);
}

t_vector2	map_size_window()
{
	t_mlx		*mlx;
	t_vector2	board_size;
	t_object	*label_x;
	t_object	*label_y;
	t_object	*slider;

	label_x = create_obj(LABEL, NULL, 10, vec2(50, 100), vec2(25, 25)
						, 0xFFFFFF, "X VALUE", NULL);
	label_y = create_obj(LABEL, NULL, 10, vec2(100, 100), vec2(25, 25)
						, 0xFFFFFF, "Y VALUE", NULL);
	mlx = setup_mlx("SELECT SIZE", vec2(0, 0));
	slider = new_slider(vec2(20, 150), 255, 0xFF0000, mlx);
	map_size_obj(mlx, label_x, label_y, slider);
	new_image(mlx, vec2(300, 300), vec2(0, 0));
	draw_object_list(mlx, mlx->obj_list);
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_mouse_hook(mlx->win, _input_mouse, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, fun_exit, mlx->mlx);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	mlx_loop(mlx->mlx);
	board_size = vec2(label_x->value, label_y->value);
	free_mlx(mlx);
	return (board_size);
}

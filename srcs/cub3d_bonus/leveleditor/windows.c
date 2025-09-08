/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:50:21 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/08 16:21:09 by dfeve            ###   ########.fr       */
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

void	map_size_obj(t_mlx *mlx, t_object *label_x, t_object *label_y)
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
}

t_vector2	map_size_window()
{
	t_mlx		*mlx;
	t_vector2	board_size;
	t_object	*label_x;
	t_object	*label_y;

	label_x = create_obj(LABEL, NULL, 10, vec2(50, 100), vec2(25, 25)
						, 0xFFFFFF, "X VALUE", NULL);
	label_y = create_obj(LABEL, NULL, 10, vec2(100, 100), vec2(25, 25)
						, 0xFFFFFF, "Y VALUE", NULL);
	mlx = setup_mlx("SELECT SIZE", vec2(0, 0));
	map_size_obj(mlx, label_x, label_y);
	new_image(mlx, vec2(300, 300), vec2(0, 0));
	draw_object_list(mlx, mlx->obj_list);
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, fun_exit, mlx->mlx);
	mlx_hook(mlx->win, ON_MOUSEDOWN, 1L << 2, _input_mouse_click_down_ex, mlx);
	mlx_hook(mlx->win, ON_MOUSEUP, 1L << 3, _input_mouse_click_up_ex, mlx);
	mlx_hook(mlx->win, ON_MOUSEMOVE, 1L << 6, _input_mouse, mlx);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	mlx_loop(mlx->mlx);
	board_size = vec2(label_x->value, label_y->value);
	free_mlx(mlx);
	return (board_size);
}

void	on_done_button_click(void *vd_mlx, int idk)
{
	t_mlx	*mlx;
	(void)idk;
	mlx = (t_mlx *)vd_mlx;
	
	
	mlx_loop_end(mlx->mlx);
}

unsigned int	*color_choose_window()
{
	t_mlx			*mlx;
	t_object		**sliders;
	t_object		*done_button;
	unsigned int	*result;

	mlx = setup_mlx("COLOR CHOOSE", vec2(0, 0));
	result = calloc(6, sizeof(unsigned int));
	sliders = calloc(6, sizeof(t_object *));
	sliders[0] = new_slider(vec2(20, 100), 255, 0xFF0000, mlx);
	sliders[1] = new_slider(vec2(20, 150), 255, 0x00FF00, mlx);
	sliders[2] = new_slider(vec2(20, 200), 255, 0x0000FF, mlx);
	sliders[3] = new_slider(vec2(500, 100), 255, 0xFF0000, mlx);
	sliders[4] = new_slider(vec2(500, 150), 255, 0x00FF00, mlx);
	sliders[5] = new_slider(vec2(500, 200), 255, 0x0000FF, mlx);
	done_button = create_obj(BUTTON, on_done_button_click, 0, vec2(270, 500), vec2(25, 15), 0xFFFFFF, "DONE", mlx);
	add_obj_to_list(&mlx->obj_list, sliders[0]);
	add_obj_to_list(&mlx->obj_list, sliders[1]);
	add_obj_to_list(&mlx->obj_list, sliders[2]);
	add_obj_to_list(&mlx->obj_list, sliders[3]);
	add_obj_to_list(&mlx->obj_list, sliders[4]);
	add_obj_to_list(&mlx->obj_list, sliders[5]);
	add_obj_to_list(&mlx->obj_list, done_button);
	new_image(mlx, mlx->screen_size, vec2(0, 0));
	draw_object_list(mlx, mlx->obj_list);
	put_imgs(mlx);
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, fun_exit, mlx->mlx);
	mlx_hook(mlx->win, ON_MOUSEDOWN, 1L << 2, _input_mouse_click_down_ex, mlx);
	mlx_hook(mlx->win, ON_MOUSEUP, 1L << 3, _input_mouse_click_up_ex, mlx);
	mlx_hook(mlx->win, ON_MOUSEMOVE, 1L << 6, _input_mouse, mlx);
	mlx_loop(mlx->mlx);
	result[0] = sliders[0]->value;
	result[1] = sliders[1]->value;
	result[2] = sliders[2]->value;
	result[3] = sliders[3]->value;
	result[4] = sliders[4]->value;
	result[5] = sliders[5]->value;
	free_mlx(mlx);
	return (result);
}

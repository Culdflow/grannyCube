/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:50:21 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/11 22:36:01 by dfeve            ###   ########.fr       */
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
	add_obj_to_list(&mlx->obj_list, obj_set_onClick(create_obj(BUTTON, vec2(1750, 450), 0xFFFFFF, "SUBMIT"), mlx_loop_end_signal, mlx));
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

void	map_size_obj(t_mlx *mlx, t_object *value_x, t_object *value_y)
{
	
	add_obj_to_list(&mlx->obj_list, obj_set_onClick(create_obj(BUTTON
					, vec2(50, 65), 0xFFFFFF, ""), modif_label_up, value_x));
	add_obj_to_list(&mlx->obj_list, create_obj(LABEL, vec2(50, 100), 0xFFFFFF
					, "X VALUE"));
	add_obj_to_list(&mlx->obj_list, obj_set_onClick(create_obj(BUTTON
					, vec2(50, 120), 0xFFFFFF, ""), modif_label_down, value_x));
	add_obj_to_list(&mlx->obj_list, obj_set_onClick(create_obj(BUTTON
					, vec2(100, 65), 0xFFFFFF, ""), modif_label_up, value_y));
	add_obj_to_list(&mlx->obj_list, create_obj(LABEL, vec2(100, 100), 0xFFFFFF
					, "Y VALUE"));
	add_obj_to_list(&mlx->obj_list, obj_set_onClick(create_obj(BUTTON
					, vec2(100, 120), 0xFFFFFF, ""), modif_label_down, value_y));
	add_obj_to_list(&mlx->obj_list, obj_set_onClick(create_obj(BUTTON
					, vec2(150, 100), 0xFFFFFF, "CREATE")
					, mlx_loop_end_signal, mlx));
	add_obj_to_list(&mlx->obj_list, value_x);
	add_obj_to_list(&mlx->obj_list, value_y);
}

t_vector2	map_size_window()
{
	t_mlx		*mlx;
	t_vector2	board_size;
	t_object	*value_x;
	t_object	*value_y;

	value_x = obj_set_val_size(create_obj(LABEL, vec2(50, 110), 0xFFFFFF, "10")
							, 10, vec2(25, 25));
	value_y = obj_set_val_size(create_obj(LABEL, vec2(100, 110), 0xFFFFFF, "10")
							, 10, vec2(25, 25));
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

void	on_done_button_click(void *vd_mlx, int idk)
{
	t_mlx	*mlx;
	(void)idk;
	mlx = (t_mlx *)vd_mlx;
	
	
	mlx_loop_end(mlx->mlx);
}

char	*rgb_to_str(unsigned int r, unsigned int g, unsigned int b)
{
	char	*result;
	char	*str_r;
	char	*str_g;
	char	*str_b;
	char	*tmp;

	str_r = ft_itoa(r);
	str_g = ft_itoa(g);
	str_b = ft_itoa(b);
	result = ft_strjoin(str_r, ", ");
	tmp = result;
	result = ft_strjoin(result, str_g);
	free(tmp);
	tmp = result;
	result = ft_strjoin(result, ", ");
	free(tmp);
	tmp = result;
	result = ft_strjoin(result, str_b);
	free(tmp);
	free(str_r);
	free(str_g);
	free(str_b);
	return (result);
}

char	**color_choose_window()
{
	t_mlx			*mlx;
	t_object		**sliders;
	t_object		*done_button;
	char			*rgb;
	char			**result;

	mlx = setup_mlx("COLOR CHOOSE", vec2(0, 0));
	result = calloc(6, sizeof(char *));
	sliders = calloc(6, sizeof(t_object *));
	sliders[0] = new_slider(vec2(20, 100), 255, 0xFF0000, mlx);
	sliders[1] = new_slider(vec2(20, 150), 255, 0x00FF00, mlx);
	sliders[2] = new_slider(vec2(20, 200), 255, 0x0000FF, mlx);
	sliders[3] = new_slider(vec2(500, 100), 255, 0xFF0000, mlx);
	sliders[4] = new_slider(vec2(500, 150), 255, 0x00FF00, mlx);
	sliders[5] = new_slider(vec2(500, 200), 255, 0x0000FF, mlx);
	sliders[0]->tag = ft_strdup("red_1");
	sliders[1]->tag = ft_strdup("green_1");
	sliders[2]->tag = ft_strdup("blue_1");
	sliders[3]->tag = ft_strdup("red_2");
	sliders[4]->tag = ft_strdup("green_2");
	sliders[5]->tag = ft_strdup("blue_2");
	done_button = obj_set_onClick(create_obj(BUTTON, vec2(270, 500), 0xFFFFFF
						, "DONE"), on_done_button_click, mlx);
	new_image(mlx, mlx->screen_size, vec2(0, 0));
	rgb = rgb_to_str(sliders[0]->value, sliders[1]->value, sliders[2]->value);
	draw_rectangle_no_fill(&mlx->imgs[0], vec2(9, 229), vec2(31, 251), 0xffffff);
	draw_rectangle(&mlx->imgs[0], vec2(10, 230), vec2(30, 250), rgb_to_hex(rgb));
	free(rgb);
	rgb = rgb_to_str(sliders[3]->value, sliders[4]->value, sliders[5]->value);
	draw_rectangle_no_fill(&mlx->imgs[0], vec2(489, 229), vec2(511, 251), 0xffffff);
	draw_rectangle(&mlx->imgs[0], vec2(490, 230), vec2(510, 250), rgb_to_hex(rgb));
	free(rgb);
	add_obj_to_list(&mlx->obj_list, sliders[0]);
	add_obj_to_list(&mlx->obj_list, sliders[1]);
	add_obj_to_list(&mlx->obj_list, sliders[2]);
	add_obj_to_list(&mlx->obj_list, sliders[3]);
	add_obj_to_list(&mlx->obj_list, sliders[4]);
	add_obj_to_list(&mlx->obj_list, sliders[5]);
	add_obj_to_list(&mlx->obj_list, done_button);
	draw_object_list(mlx, mlx->obj_list);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, fun_exit, mlx->mlx);
	mlx_hook(mlx->win, ON_MOUSEDOWN, 1L << 2, _input_mouse_click_down_ex, mlx);
	mlx_hook(mlx->win, ON_MOUSEUP, 1L << 3, _input_mouse_click_up_ex, mlx);
	mlx_hook(mlx->win, ON_MOUSEMOVE, 1L << 6, _input_mouse, mlx);
	mlx_loop(mlx->mlx);
	result[0] = ft_itoa(sliders[0]->value);
	result[1] = ft_itoa(sliders[1]->value);
	result[2] = ft_itoa(sliders[2]->value);
	result[3] = ft_itoa(sliders[3]->value);
	result[4] = ft_itoa(sliders[4]->value);
	result[5] = ft_itoa(sliders[5]->value);
	free_mlx(mlx);
	return (result);
}

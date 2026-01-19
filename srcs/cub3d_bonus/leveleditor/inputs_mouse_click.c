/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_mouse_click.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:53:10 by dfeve             #+#    #+#             */
/*   Updated: 2026/01/19 21:00:32 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub3d_bonus.h"

int	_input_mouse_click_down(int keycode, int x, int y, void *void_mlx)
{
	t_vector2	pos;
	t_mlx		*mlx;
	char		el;

	pos.x = x;
	pos.y = y;
	mlx = (t_mlx *)void_mlx;
	if (keycode == M_CLK_L)
	{
		check_if_obj_clicked(pos, mlx->obj_list);
		el = get_el_from_board(pos, mlx->board_size, mlx->board);
		mlx->is_clicking = TRUE;
		if (el != '0')
			mlx->turning_to = '0';
		else
			mlx->turning_to = '1';
		del_images(mlx);
		board_clicked(pos, mlx->board_size, mlx->board, mlx->turning_to);
		new_image(mlx, mlx->screen_size, vec2(0, 0));
		draw_board(mlx, 0xFFFFFF, mlx->board, mlx->board_size);
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
	}
	return (1);
}

int	_input_mouse_click_down_ex(int keycode, int x, int y, t_mlx *mlx)
{
	mlx->mouse_pos.x = x;
	mlx->mouse_pos.y = y;
	if (keycode == M_CLK_L)
	{
		mlx->is_clicking = TRUE;
		check_if_obj_clicked(mlx->mouse_pos, mlx->obj_list);
		del_images(mlx);
		new_image(mlx, mlx->screen_size, vec2(0, 0));
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
		draw_sliders(mlx);
	}
	return (1);
}

int	_input_mouse_click_up_ex(int keycode, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (keycode == M_CLK_L)
	{
		if (mlx)
			mlx->is_clicking = FALSE;
	}
	return (1);
}

int	_input_mouse_click_up(int keycode, int x, int y, void *void_mlx)
{
	t_mlx	*mlx;

	(void)x;
	(void)y;
	mlx = (t_mlx *)void_mlx;
	if (keycode == M_CLK_L)
	{
		if (mlx)
			mlx->is_clicking = FALSE;
	}
	return (1);
}

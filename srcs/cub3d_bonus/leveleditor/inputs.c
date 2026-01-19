/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:53:10 by dfeve             #+#    #+#             */
/*   Updated: 2026/01/19 20:20:12 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub3d_bonus.h"

int	_input(int keycode, void *void_mlx)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)void_mlx;
	mlx->turning_to = '1';
	if (keycode == K_ESC)
	{
		exit(0);
		return (1);
	}
	if (keycode == K_X)
		mlx->turning_to = 'N';
	if (keycode == K_E)
		mlx->turning_to = 'F';
	del_images(mlx);
	board_clicked(mlx->mouse_pos, mlx->board_size, mlx->board,
		mlx->turning_to);
	new_image(mlx, mlx->screen_size, vec2(0, 0));
	draw_board(mlx, 0xFFFFFF, mlx->board, mlx->board_size);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	return (1);
}

int	_input_mouse_ex(int x, int y, t_mlx *mlx)
{
	t_vector2	pos;

	pos.x = x;
	pos.y = y;
	mlx->mouse_pos.x = x;
	mlx->mouse_pos.y = y;
	if (mlx->is_clicking)
	{
		check_if_obj_clicked(pos, mlx->obj_list);
		del_images(mlx);
		new_image(mlx, mlx->screen_size, vec2(0, 0));
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
	}
	return (1);
}

void	step_input_mouse(t_mlx *mlx)
{
	draw_sliders(mlx);
	draw_object_list(mlx, mlx->obj_list);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
}

int	_input_mouse(int x, int y, t_mlx *mlx)
{
	t_vector2	pos;

	pos.x = x;
	pos.y = y;
	mlx->mouse_pos.x = x;
	mlx->mouse_pos.y = y;
	if (mlx->is_clicking)
	{
		check_if_obj_clicked(pos, mlx->obj_list);
		del_images(mlx);
		new_image(mlx, mlx->screen_size, vec2(0, 0));
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
	}
	step_input_mouse(mlx);
	return (1);
}

int	_input_mouse_board(int keycode, int x, t_mlx *mlx)
{
	t_vector2	pos;

	pos.y = x;
	pos.x = keycode;
	mlx->mouse_pos = pos;
	if (mlx->is_clicking == TRUE)
	{
		del_images(mlx);
		board_clicked(pos, mlx->board_size, mlx->board, mlx->turning_to);
		new_image(mlx, mlx->screen_size, vec2(0, 0));
		draw_board(mlx, 0xFFFFFF, mlx->board, mlx->board_size);
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
	}
	return (1);
}

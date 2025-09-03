/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:53:10 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/01 18:02:58 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	_input(int keycode, void *void_mlx)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)void_mlx;
	mlx->turning_to = '1';
	if (keycode == K_ESC)
		exit(0);
	if (keycode == K_X)
		mlx->turning_to = 'N';
	return (1);
}

int	_input_mouse(int keycode, int x, int y, t_mlx *mlx)
{
	t_vector2	pos;

	pos.x = x;
	pos.y = y;
	mlx->mouse_pos.x = x;
	mlx->mouse_pos.y = y;
	if (keycode == M_CLK_L)
	{
		check_if_obj_clicked(pos, mlx->obj_list);
		del_images(mlx);
		new_image(mlx, vec2(300, 300), vec2(0, 0));
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
	}
	return (1);
}

int	_input_mouse_board(int keycode, int x, t_mlx *mlx)
{
	t_vector2	pos;

	pos.y = x;
	pos.x = keycode;
	if (mlx->is_clicking == TRUE)
	{
		del_images(mlx);
		board_clicked(pos, mlx->board_size, mlx->board, mlx->turning_to);
		new_image(mlx, mlx->screen_size, vec2(0, 0));
		draw_board(mlx, 0xFFFFFF, mlx->board, mlx->board_size);
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
	}
	else if(mlx->turning_to == 'N')
	{
		del_images(mlx);
		board_clicked(pos, mlx->board_size, mlx->board, mlx->turning_to);
		new_image(mlx, mlx->screen_size, vec2(0, 0));
		draw_board(mlx, 0xFFFFFF, mlx->board, mlx->board_size);
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
		mlx->turning_to = '1';
	}
	return (1);
}

int	_input_mouse_click_down(int keycode, int x, int y, void *void_mlx)
{
	t_vector2	pos;
	t_mlx		*mlx;
	pos.x = x;
	pos.y = y;
	char	el;
	mlx = (t_mlx *)void_mlx;
	if (keycode == M_CLK_L)
	{
		check_if_obj_clicked(pos, mlx->obj_list);
		el = get_el_from_board(pos, mlx->board_size, mlx->board);
		mlx->is_clicking = TRUE;
		if (el == '1')
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
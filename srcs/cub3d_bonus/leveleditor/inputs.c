/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:53:10 by dfeve             #+#    #+#             */
/*   Updated: 2025/10/03 02:08:30 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	_input_file(int keycode, t_mlx *mlx)
{
	t_dir_files	*cursor;
	char		*tmp;
	char		*dir;

	cursor = mlx->files;
	dir = NULL;
	while (cursor)
	{
		if (cursor->on_cursor == TRUE)
		{
			if (keycode == K_AR_D && cursor->next)
			{
				printf("down\n");
				cursor->on_cursor = FALSE;
				cursor->next->on_cursor = TRUE;
				break ;
			}
			if (keycode == K_AR_U && cursor->prev)
			{
				printf("up\n");
				cursor->on_cursor = FALSE;
				cursor->prev->on_cursor = TRUE;
			}
			if (keycode == K_SP)
			{
				if (cursor->type == T_DIRECTORY)
				{
					tmp = ft_strjoin(mlx->cur_dir, "/");
					dir = ft_strjoin(tmp, cursor->name);
					free(tmp);
					free(mlx->cur_dir);
					mlx->cur_dir = dir;
					free_dir_files(mlx->files);
					mlx->files = get_files_from_dir(dir);
					free_object_list(mlx->obj_list);
					mlx->obj_list = NULL;
					break ;
				}
				else
				{
					if (cursor->status != SELECTED)
						cursor->status = SELECTED;
					else
						cursor->status = NOT_SELECTED;
					mlx_loop_end(mlx->mlx);
				}
			}
		}
		cursor = cursor->next;
	}
	del_images(mlx);
	new_image(mlx, mlx->screen_size, vec2(0, 0));
	draw_files_window(mlx->files, mlx);
	return (0);
}

int	_input(int keycode, void *void_mlx)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)void_mlx;
	mlx->turning_to = '1';
	if (keycode == K_ESC)
		exit(0);
	if (keycode == K_X)
	{
		mlx->turning_to = 'N';
		del_images(mlx);
		board_clicked(mlx->mouse_pos, mlx->board_size, mlx->board, mlx->turning_to);
		new_image(mlx, mlx->screen_size, vec2(0, 0));
		draw_board(mlx, 0xFFFFFF, mlx->board, mlx->board_size);
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
	}
	return (1);
}

int _input_mouse_ex(int x, int y, t_mlx *mlx)
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

int	_input_mouse(int x, int y, t_mlx *mlx)
{
	t_vector2	pos;
	char		*rgb;

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
	rgb = rgb_to_str(get_object_from_tag(mlx->obj_list, "red_1")->value, get_object_from_tag(mlx->obj_list, "green_1")->value, get_object_from_tag(mlx->obj_list, "blue_1")->value);
	draw_rectangle_no_fill(&mlx->imgs[0], vec2(9, 229), vec2(31, 251), 0xffffff);
	draw_rectangle(&mlx->imgs[0], vec2(10, 230), vec2(30, 250), rgb_to_hex(rgb));
	free(rgb);
	rgb = rgb_to_str(get_object_from_tag(mlx->obj_list, "red_2")->value, get_object_from_tag(mlx->obj_list, "green_2")->value, get_object_from_tag(mlx->obj_list, "blue_2")->value);
	draw_rectangle_no_fill(&mlx->imgs[0], vec2(489, 229), vec2(511, 251), 0xffffff);
	draw_rectangle(&mlx->imgs[0], vec2(490, 230), vec2(510, 250), rgb_to_hex(rgb));
	free(rgb);
	draw_object_list(mlx, mlx->obj_list);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
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
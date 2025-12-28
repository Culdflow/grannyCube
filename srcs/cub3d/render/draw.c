/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:16:16 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/28 19:14:13 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (color != 0xe29c9c)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	calculate_offset(t_vector2 start, t_vector2 end, float *ox, float *oy)
{
	t_vector2	diff;
	float		diff_x;
	float		diff_y;

	diff = sub_vec2(end, start);
	diff_x = diff.x;
	diff_y = diff.y;
	if (abs(diff.x) > abs(diff.y))
	{
		*ox = 1;
		*oy = fabsf(diff_y) / fabsf(diff_x);
	}
	else
	{
		*oy = 1;
		*ox = fabsf(diff_x) / fabsf(diff_y);
	}
	if (diff_x < 0)
		*ox = *ox * -1;
	if (diff_y < 0)
		*oy = *oy * -1;
}

void	draw_line(t_img *data, t_vector2 start, t_vector2 end, int color)
{
	float	x;
	float	y;
	float	ox;
	float	oy;
	int		i;

	clamp_vec2(&start, vec2(0, 0), vec2(1920, 1080));
	clamp_vec2(&end, vec2(0, 0), vec2(1920, 1080));
	x = start.x;
	y = start.y;
	ox = 0;
	oy = 0;
	i = 0;
	calculate_offset(start, end, &ox, &oy);
	while (i <= abs(sub_vec2(end, start).x) || i <= abs(sub_vec2(end, start).y))
	{
		my_mlx_pixel_put(data, (int)x, (int)y, color);
		x += ox;
		y += oy;
		i++;
	}
}

void	d_b_rec(int fill, t_vector2 *start_end, t_mlx *mlx
		, int color)
{
	if (fill)
		draw_rectangle(&mlx->imgs[0], add_vec2(start_end[0], vec2(20, 20)),
			add_vec2(start_end[1], vec2(20, 20)), color);
	else
		draw_rectangle_no_fill(&mlx->imgs[0], add_vec2(start_end[0],
				vec2(20, 20)), add_vec2(start_end[1], vec2(20, 20)), color);
}

void	draw_board(t_mlx *mlx, int color1, char **board, t_vector2 board_size)
{
	t_vector2	cursor;
	t_vector2	screen_size;
	t_vector2	start_end[2];

	screen_size = mlx->minimap_size;
	cursor = vec2(0, 0);
	while (cursor.y < board_size.y && board && board[cursor.y])
	{
		cursor.x = -1;
		while ((++cursor.x) < board_size.x && board[cursor.y][cursor.x])
		{
			start_end[0] = mul_vec2(cursor, div_vec2(screen_size, board_size));
			start_end[1] = mul_vec2(add_vec2(cursor, vec2(1, 1)),
					div_vec2(screen_size, board_size));
			if (board[cursor.y][cursor.x] == '0')
				d_b_rec(0, start_end, mlx, color1);
			else if (board[cursor.y][cursor.x] == '1')
				d_b_rec(1, start_end, mlx, color1);
			else if (board[cursor.y][cursor.x] == 'N')
				d_b_rec(1, start_end, mlx, 0xFF0000);
			else if (board[cursor.y][cursor.x] == 'F')
				d_b_rec(1, start_end, mlx, 0x0000FF);
		}
		cursor.y++;
	}
}

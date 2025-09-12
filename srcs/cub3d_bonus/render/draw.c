/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:16:16 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/12 02:49:36 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	if (color != 0xe29c9c)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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

void	draw_rectangle(t_img *data, t_vector2 start, t_vector2 end, int color)
{
	t_vector2	cursor;
	t_vector2	goal;
	int			x;

	if (!data)
		return ;
	clamp_vec2(&start, vec2(0, 0), vec2(1920, 1080));
	clamp_vec2(&end, vec2(0, 0), vec2(1920, 1080));
	cursor = vec2_make_start(start, end);
	x = cursor.x;
	goal = vec2_make_end(start, end);
	while (cursor.y <= goal.y)
	{
		cursor.x = x;
		while (cursor.x <= goal.x)
		{
			my_mlx_pixel_put(data, cursor.x, cursor.y, color);
			cursor.x++;
		}
		cursor.y++;
	}
}

void	draw_rectangle_no_fill(t_img *data, t_vector2 start, t_vector2 end, int color)
{
	int	i;

	i = start.x;
	clamp_vec2(&start, vec2(0, 0), vec2(1920, 1080));
	clamp_vec2(&end, vec2(0, 0), vec2(1920, 1080));
	while (i <= end.x)
	{
		my_mlx_pixel_put(data, i, start.y, color);
		my_mlx_pixel_put(data, i++ , end.y, color);
	}
	i = start.y;
	while (i <= end.y)
	{
		my_mlx_pixel_put(data, start.x, i, color);
		my_mlx_pixel_put(data, end.x , i++, color);
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_length) + (x * img.bits_per_pixel / 8))));
}

void	put_img_to_img(t_img *dst, t_img src, int x, int y)
{
	int i;
	int j;

	i = 0;
	while(i < src.size.y)
	{
		j = 0;
		while (j < src.size.x) {
			my_mlx_pixel_put(dst, x + j, y + i, get_pixel_img(src, j, i));
			j++;
		}
		i++;
	}
}

void	draw_board(t_mlx *mlx, int	color1, char **board, t_vector2 board_size)
{
	t_vector2	cursor;
	t_vector2	screen_size;
	t_vector2	start;
	t_vector2	end;

	screen_size = mlx->minimap_size;
	cursor = vec2(0, 0);
	while (cursor.y < board_size.y && board && board[cursor.y])
	{
		cursor.x = 0;
		while (cursor.x < board_size.x && board[cursor.y][cursor.x])
		{
			start = mul_vec2(cursor, div_vec2(screen_size, board_size));
			end = mul_vec2(add_vec2(cursor, vec2(1, 1)), div_vec2(screen_size, board_size));
			if (board[cursor.y][cursor.x] == '0')
				draw_rectangle_no_fill(&mlx->imgs[0], add_vec2(start, vec2(20, 20)), add_vec2(end, vec2(20, 20)), color1);
			else if (board[cursor.y][cursor.x] == '1')
				draw_rectangle(&mlx->imgs[0], add_vec2(start, vec2(20, 20)), add_vec2(end, vec2(20, 20)), color1);
			else if (board[cursor.y][cursor.x] == 'N')
				draw_rectangle(&mlx->imgs[0], add_vec2(start, vec2(20, 20)), add_vec2(end, vec2(20, 20)), 0xFF0000);
			cursor.x++;
		}
		cursor.y++;
	}
}

void	draw_object(t_mlx *mlx, t_object *obj)
{
	char *string;

	string = NULL;
	if (obj->type == BUTTON)
	{
		draw_rectangle(&mlx->imgs[0], obj->pos, add_vec2(obj->pos, obj->size), obj->color);
		mlx_string_put(mlx->mlx, mlx->win, obj->pos.x, obj->pos.y - 10, 0xFF0000, obj->tag);
	}
	else if (obj->type == LABEL)
	{
		string = ft_itoa(obj->value);
		mlx_string_put(mlx->mlx, mlx->win, obj->pos.x , obj->pos.y, obj->color, obj->tag);
		mlx_string_put(mlx->mlx, mlx->win, obj->pos.x + 10 , obj->pos.y + 15, obj->color, string);
		free(string);
	}
	else if (obj->type == SLIDER)
	{
		draw_line(&mlx->imgs[0], obj->pos, add_vec2(obj->pos, vec2(obj->size.x - 10, 0)), obj->color);
		draw_rectangle(&mlx->imgs[0], add_vec2(obj->pos, vec2(obj->value - 2, -5)), add_vec2(obj->pos, vec2(obj->value + 2, 5)), obj->color);
	}
}

void	draw_object_list(t_mlx *mlx, t_object_list *obj_lst)
{
	while (obj_lst)
	{
		draw_object(mlx, obj_lst->object);
		obj_lst = obj_lst->next;
	}
}

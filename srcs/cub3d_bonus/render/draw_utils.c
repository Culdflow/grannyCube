/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:47:23 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/16 16:48:46 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

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

void	draw_rectangle_no_fill(t_img *data, t_vector2 start, t_vector2 end,
	int color)
{
	int	i;

	i = start.x;
	clamp_vec2(&start, vec2(0, 0), vec2(1920, 1080));
	clamp_vec2(&end, vec2(0, 0), vec2(1920, 1080));
	while (i <= end.x)
	{
		my_mlx_pixel_put(data, i, start.y, color);
		my_mlx_pixel_put(data, i++, end.y, color);
	}
	i = start.y;
	while (i <= end.y)
	{
		my_mlx_pixel_put(data, start.x, i, color);
		my_mlx_pixel_put(data, end.x, i++, color);
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_length)
			+ (x * img.bits_per_pixel / 8))));
}

void	draw_object(t_mlx *mlx, t_object *obj)
{
	char	*string;

	string = NULL;
	if (obj->type == BUTTON)
	{
		draw_rectangle(&mlx->imgs[0], obj->pos, add_vec2(obj->pos, obj->size),
			obj->color);
		mlx_string_put(mlx->mlx, mlx->win, obj->pos.x, obj->pos.y - 10,
			0xFF0000, obj->tag);
	}
	else if (obj->type == LABEL)
		mlx_string_put(mlx->mlx, mlx->win, obj->pos.x, obj->pos.y, obj->color,
			obj->tag);
	else if (obj->type == SLIDER)
	{
		draw_line(&mlx->imgs[0], obj->pos, add_vec2(obj->pos,
				vec2(obj->size.x - 10, 0)), obj->color);
		draw_rectangle(&mlx->imgs[0], add_vec2(obj->pos,
				vec2(obj->value - 2, -5)), add_vec2(obj->pos,
				vec2(obj->value + 2, 5)), obj->color);
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

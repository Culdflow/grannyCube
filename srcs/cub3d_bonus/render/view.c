/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 05:44:21 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/16 18:29:29 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

float	find_x_for_img(t_ray *ray, t_img img)
{
	float	mul_vector;
	float	result;

	if (ray->wall_hit_dir == NORTH || ray->wall_hit_dir == SOUTH
		|| ray->wall_hit_dir == FOG_NORTH_SOUTH
		|| ray->wall_hit_dir == DOOR_NORTH_SOUTH)
		mul_vector = ft_fmodulf((float)ray->end_pos.x, 100) / 100;
	else
		mul_vector = ft_fmodulf((float)ray->end_pos.y, 100) / 100;
	result = ((float)img.size.x) * mul_vector;
	ft_fclampf(&result, 0, (float)img.size.x - 1);
	return (result);
}

t_img	get_texture_line(t_ray *cursor, t_data *data)
{
	if (cursor->wall_hit_dir == NORTH)
		return (*(data->textures->north_texture));
	else if (cursor->wall_hit_dir == SOUTH)
		return (*(data->textures->south_texture));
	else if (cursor->wall_hit_dir == EAST)
		return (*(data->textures->east_texture));
	else if (cursor->wall_hit_dir == WEST)
		return (*(data->textures->west_texture));
	else if (cursor->wall_hit_dir == DOOR_NORTH_SOUTH
		|| cursor->wall_hit_dir == DOOR_EAST_WEST)
		return (*(data->textures->door_texture));
	else
		return (*(data->textures->fog_texture));
}



void	put_texture_line(t_ray *ray, int line_height, t_vector2 line_start_pos,
		t_data *data)
{
	int		y;
	int		x;
	t_img	img;
	float	img_x;
	float	img_y;

	x = line_start_pos.x;
	y = line_start_pos.y - 1;
	img = get_texture_line(ray, data);
	while (y <= line_start_pos.y + line_height)
	{
		img_x = find_x_for_img(ray, img);
		img_y = ((((float)y - (float)line_start_pos.y) / line_height)
				* img.size.y);
		ft_fclampf(&img_y, 0, img.size.y - 1);
		if (x > 0 && x < data->mlx->screen_size.x && ++y > 0
			&& y < data->mlx->screen_size.y)
		{
			if (ray->wall_hit_dir == FOG_NORTH_SOUTH
				|| ray->wall_hit_dir == FOG_EAST_WEST)
				my_mlx_pixel_put(&data->mlx->imgs[0], x, y,
					get_pixel_img(img, x, y - line_start_pos.y));
			else if (ray->wall_hit_dir == SOUTH || ray->wall_hit_dir == EAST
				|| ray->wall_hit_dir == DOOR_NORTH_SOUTH)
				my_mlx_pixel_put(&data->mlx->imgs[0], x, y,
					get_pixel_img(img, (int)img_x, (int)img_y));
			else
				my_mlx_pixel_put(&data->mlx->imgs[0], x, y,
					(get_pixel_img(img, img.size.x - (int)img_x,
							(int)img_y) & 0xfefefe) >> 1);
		}
	}
}

void	draw_3d_line(t_data *data, int line_height, t_vector2 line_start_pos,
	t_ray *cursor)
{
	put_texture_line(cursor, line_height, line_start_pos, data);
}

void	draw_lines(t_data *data, t_vector2 *line_start_pos, t_ray *cursor,
	t_vector2 screen_size)
{
	int	line_height;

	line_height = (100 * screen_size.y) / cursor->length;
	line_start_pos->y = (screen_size.y / 2) - (line_height / 2);
	draw_3d_line(data, line_height, *line_start_pos, cursor);
	line_start_pos->x++;
	draw_3d_line(data, line_height, *line_start_pos, cursor);
	line_start_pos->x++;
	draw_3d_line(data, line_height, *line_start_pos, cursor);
	line_start_pos->x++;
	draw_3d_line(data, line_height, *line_start_pos, cursor);
	line_start_pos->x++;
}

void	check_fisheye(float *ca)
{
	if (*ca < 0)
		*ca += 2 * M_PI;
	if (*ca > 2 * M_PI)
		*ca -= 2 * M_PI;
}

void	draw_3d_view(t_data *data, t_vector2 screen_size)
{
	t_vector2	line_start_pos;
	float		ca;
	float		player_angle_rad;
	float		ray_angle_rad;
	t_ray		*cursor;

	line_start_pos = vec2(0, 0);
	cursor = data->ray_list->ray_list;
	ca = 0;
	player_angle_rad = (data->player->angle * M_PI) / 180;
	ray_angle_rad = 0;
	while (cursor && line_start_pos.x <= screen_size.x)
	{
		ray_angle_rad = (cursor->angle * M_PI) / 180;
		ca = ft_fabsf(player_angle_rad - ray_angle_rad);
		check_fisheye(&ca);
		cursor->length = cursor->length * cos(ca);
		if (cursor->wall_hit_dir == FOG_EAST_WEST
			|| cursor->wall_hit_dir == FOG_NORTH_SOUTH)
			cursor->length = data->mlx->dov * 100;
		draw_lines(data, &line_start_pos, cursor, screen_size);
		cursor = cursor->next_ray;
	}
}

void	draw_floor_ceiling(t_data *data, t_vector2 screen_size,
	t_textures *textures)
{
	draw_rectangle(&data->mlx->imgs[0], vec2(0, screen_size.y / 2),
		screen_size, textures->floor_color);
	draw_rectangle(&data->mlx->imgs[0], vec2(0, 0),
		vec2(screen_size.x, screen_size.y / 2), textures->ceiling_color);
}

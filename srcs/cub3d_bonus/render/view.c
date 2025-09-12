/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 05:44:21 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/12 04:19:55 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

float	find_x_for_img(t_ray *ray, t_img img)
{
	float	mul_vector;

	if (ray->wall_hit_dir == NORTH || ray->wall_hit_dir == SOUTH || ray->wall_hit_dir == FOG_NORTH_SOUTH)
		mul_vector = ft_fmodulf((float)ray->end_pos.x, 100) / 100;
	else
		mul_vector = ft_fmodulf((float)ray->end_pos.y, 100) / 100;
	return (((float)img.size.x) * mul_vector);
}

void	put_texture_line(t_ray *ray, int line_height, t_vector2 line_start_pos, t_img img, t_mlx *mlx)
{
	int		y;
	int		x;
	float	img_x;
	float	img_y;

	x = line_start_pos.x;
	y = line_start_pos.y;
	img_x = 0;
	img_y = 0;
	while (y <= line_start_pos.y + line_height)
	{
		// printf("x = %f\ny = %f\n", img_x, img_y);
		img_x = find_x_for_img(ray, img);
		img_y = ((((float)y - (float)line_start_pos.y) / line_height) * img.size.y);
		if (x > 0 && x < mlx->screen_size.x && y > 0 && y < mlx->screen_size.y)
		{
			if (ray->wall_hit_dir == NORTH || ray->wall_hit_dir == WEST)
				my_mlx_pixel_put(&mlx->imgs[0], x, y, get_pixel_img(img, img.size.x - (int)img_x, (int)img_y));
			else
				my_mlx_pixel_put(&mlx->imgs[0], x, y, (get_pixel_img(img, img_x, (int)img_y) & 0xfefefe) >> 1);
		}
		y++;
	}
}

void	draw_3d_line(t_data *data, int line_height, t_vector2 line_start_pos, t_ray *cursor)
{
	if (cursor->wall_hit_dir == NORTH)
		put_texture_line(cursor, line_height, line_start_pos, *(data->textures->north_texture), data->mlx);
	else if (cursor->wall_hit_dir == SOUTH)
		put_texture_line(cursor, line_height, line_start_pos, *(data->textures->south_texture), data->mlx);
	else if (cursor->wall_hit_dir == EAST)
		put_texture_line(cursor, line_height, line_start_pos, *(data->textures->east_texture), data->mlx);
	else if (cursor->wall_hit_dir == WEST)
		put_texture_line(cursor, line_height, line_start_pos, *(data->textures->west_texture), data->mlx);
	else
		put_texture_line(cursor, line_height, line_start_pos, *(data->textures->fog_texture), data->mlx);	
}

void	draw_3d_view(t_data *data, t_vector2 screen_size)
{
	t_vector2	line_start_pos;
	int			line_height;
	float		ca;
	float		player_angle_rad;
	float		ray_angle_rad;
	t_ray		*cursor;

	line_start_pos = vec2(0, 0);
	cursor = data->ray_list->ray_list;
	line_height = 0;
	ca = 0;
	player_angle_rad = (data->player->angle * M_PI) / 180;
	ray_angle_rad = 0;
	while (cursor && line_start_pos.x <= screen_size.x)
	{
		ray_angle_rad = (cursor->angle * M_PI) / 180;
		ca = ft_fabsf(ft_fabsf(player_angle_rad - ray_angle_rad));
		if (ca < 0)
			ca += 2 * M_PI;
		if (ca > 2 * M_PI)						//supposed to fix fisheye but doesnt work
			ca -= 2 * M_PI;
		cursor->length = cursor->length * cos(ca);
		if (cursor->wall_hit_dir == FOG_EAST_WEST || cursor->wall_hit_dir == FOG_NORTH_SOUTH)
			cursor->length = data->mlx->dov * 100;
		line_height = (100 * screen_size.y) / cursor->length;
		line_start_pos.y = (screen_size.y / 2) - (line_height / 2);
		draw_3d_line(data, line_height, line_start_pos, cursor);
		line_start_pos.x++;
		draw_3d_line(data, line_height, line_start_pos, cursor);
		line_start_pos.x++;
		draw_3d_line(data, line_height, line_start_pos, cursor);
		line_start_pos.x++;
		draw_3d_line(data, line_height, line_start_pos, cursor);
		line_start_pos.x++;
		cursor = cursor->next_ray;
	}
}

void	draw_floor_ceiling(t_data *data, t_vector2 screen_size, t_textures *textures)
{
	draw_rectangle(&data->mlx->imgs[0], vec2(0, screen_size.y / 2), screen_size, textures->floor_color);
	draw_rectangle(&data->mlx->imgs[0], vec2(0, 0), vec2(screen_size.x, screen_size.y / 2), textures->ceiling_color);
}


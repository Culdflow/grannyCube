/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpecquer <jpecquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 05:44:21 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/17 17:22:08 by jpecquer         ###   ########.fr       */
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

void	step_put_texture_line(t_ptl *all, float img_y, int y, int x)
{
	t_img		img;
	float		img_x;

	img = get_texture_line(all->ray, all->data);
	img_x = find_x_for_img(all->ray, img);
	if (all->ray->wall_hit_dir == FOG_NORTH_SOUTH
		|| all->ray->wall_hit_dir == FOG_EAST_WEST)
		my_mlx_pixel_put(&all->data->mlx->imgs[0], x, y,
			get_pixel_img(img, x, y - all->line_start_pos.y));
	else if (all->ray->wall_hit_dir == SOUTH || all->ray->wall_hit_dir == EAST
		|| all->ray->wall_hit_dir == DOOR_NORTH_SOUTH)
		my_mlx_pixel_put(&all->data->mlx->imgs[0], x, y,
			get_pixel_img(img, (int)img_x, (int)img_y));
	else
		my_mlx_pixel_put(&all->data->mlx->imgs[0], x, y,
			(get_pixel_img(img, img.size.x - (int)img_x,
					(int)img_y) & 0xfefefe) >> 1);
	y++;
}

void	put_texture_line(t_ray *ray, int line_height, t_vector2 line_start_pos,
		t_data *data)
{
	t_ptl	all;
	int		y;
	int		x;
	t_img	img;
	float	img_y;

	all.ray = ray;
	all.line_height = line_height;
	all.line_start_pos = line_start_pos;
	all.data = data;
	x = line_start_pos.x;
	y = line_start_pos.y;
	img = get_texture_line(ray, data);
	while (y <= line_start_pos.y + line_height)
	{
		img_y = ((((float)y - (float)line_start_pos.y) / line_height)
				* img.size.y);
		ft_fclampf(&img_y, 0, img.size.y - 1);
		if (x > 0 && x < data->mlx->screen_size.x && y > 0
			&& y < data->mlx->screen_size.y)
		{
			step_put_texture_line(&all, img_y, y, x);
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:48:43 by jpecquer          #+#    #+#             */
/*   Updated: 2026/01/18 03:09:29 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub3d_bonus.h"

void	draw_3d_line(t_data *data, int line_height, t_vector2 line_start_pos,
	t_ray *cursor)
{
	put_texture_line(cursor, line_height, line_start_pos, data);
}

void	draw_lines(t_data *data, t_vector2 *line_start_pos, t_ray *cursor,
	t_vector2 screen_size)
{
	int	line_height;

	line_height = (CUBESIZE * screen_size.y) / cursor->length;
	line_start_pos->y = (screen_size.y / 2) - (line_height / 2);
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
			cursor->length = data->mlx->dov * CUBESIZE;
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

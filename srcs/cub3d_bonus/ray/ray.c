/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:18:41 by dfeve             #+#    #+#             */
/*   Updated: 2025/10/03 02:28:25 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

float wtf_sqrt( float number )
{
	float		x2;
	float		y;
	int32_t		i;

	if (number <= 0.0F)
		return (0.0F);
	x2 = number * 0.5F;
	y = number;
	i = *(int32_t *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *)&i;
	y = y * (1.5F - (x2 * y * y));
	return (number * y);
}

float	ray_get_length(t_vector2 start_pos, t_vector2 end_pos)
{
	float	length_x;
	float	length_y;
	float	result;

	length_x = abs(end_pos.x - start_pos.x);
	length_y = abs(end_pos.y - start_pos.y);
	result = wtf_sqrt((length_x * length_x) + (length_y * length_y));
	return (result);//theoreme de pythagore
}

t_vector2	ray_check_horizontal_lines(t_vector2 start_pos, float angle, t_mlx *mlx)
{
	float	a_tan;
	float	ry;
	float	rad;
	float	rx;
	float	oy;
	float	ox;
	int		dov;

	dov = 0;
	rad = (angle * M_PI) / 180;
	a_tan = -1 / tan(rad);
	ry = start_pos.y;
	rx = 0;
	oy = 0;
	ox = 0;
	if (rad > M_PI)
	{
		ry -= (int)ry % 100 + 0.001;
		rx = (start_pos.y - ry) * a_tan + start_pos.x;
		oy = -100;
		ox = (-1 * oy) * a_tan;
	}
	if (rad < M_PI)
	{
		ry += (100 - ((int)ry % 100));
		rx = (start_pos.y - ry) * a_tan + start_pos.x;
		oy = 100;
		ox = (-1 * oy) * a_tan;
	}
	if (rad == 0 || rad == M_PI)
	{
		rx = start_pos.x;
		ry = start_pos.y;
		dov = mlx->dov;
	}
	while (is_out_of_bounds(div_vec2(vec2((int)rx, (int)ry), vec2(100, 100)), mlx->board_size) == FALSE)
	{
		int grid_x = (int)(rx / 100);
		int grid_y = (int)(ry / 100);
		if (mlx->board[grid_y][grid_x] == '1' || dov >= mlx->dov)
			break ;
		rx += ox;
		ry += oy;
		dov++;
	}
	return (vec2((int)rx, (int)ry));
}

t_vector2	ray_check_vertical_lines(t_vector2 start_pos, float angle, t_mlx *mlx)
{
	float	n_tan;
	float	rad;
	float	ry;
	float	rx;
	float	oy;
	float	ox;
	int		dov;

	dov = 0;
	rad = (angle * M_PI) / 180;
	n_tan = -1 * tan(rad);
	ry = 0;
	rx = start_pos.x;
	oy = 0;
	ox = 0;
	if (rad < M_2PI || rad > M_3PI)
	{
		rx += 100 - ((int)rx % 100);
		ry = (start_pos.x - rx) * n_tan + start_pos.y;
		ox = 100;
		oy = (-1 * ox) * n_tan;
	}
	if (rad > M_2PI && rad < M_3PI)
	{
		rx -= ((int)rx % 100) + 0.01;
		ry = (start_pos.x - rx) * n_tan + start_pos.y;
		ox = -100;
		oy = (-1 * ox) * n_tan;
	}
	if (rad == M_2PI || rad == M_3PI)
	{
		rx = start_pos.x;
		ry = start_pos.y;
		dov = mlx->dov;
	}
	while (is_out_of_bounds(div_vec2(vec2((int)rx, (int)ry), vec2(100, 100)), mlx->board_size) == FALSE)
	{
		int grid_x = (int)(rx / 100);
		int grid_y = (int)(ry / 100);
		if (mlx->board[grid_y][grid_x] == '1' || dov >= mlx->dov)
			break ;
		rx += ox;
		ry += oy;
		dov++;
	}
	return (vec2((int)rx, (int)ry));
}

t_vector2	ray_get_end_pos(t_ray *ray, t_vector2 start_pos, float angle, t_mlx *mlx)
{
	t_vector2	horizontal_lines;
	t_vector2	vertical_lines;
	float		h_length;
	float		v_length;

	horizontal_lines = ray_check_horizontal_lines(start_pos, angle, mlx);
	vertical_lines = ray_check_vertical_lines(start_pos, angle, mlx);
	v_length = ray_get_length(start_pos, vertical_lines);
	h_length = ray_get_length(start_pos, horizontal_lines);
	if ((v_length <= h_length && (int)v_length > 0) || (int)h_length <= 0 )//|| (int)h_length >= 10000
	{
		if (angle <= 90 || angle > 270)
			ray->wall_hit_dir = EAST;
		else
			ray->wall_hit_dir = WEST;
		return (vertical_lines);
	}
	if (angle <= 180)
		ray->wall_hit_dir = NORTH;
	else
		ray->wall_hit_dir = SOUTH;
	return (horizontal_lines);
}

t_ray	*new_ray(t_vector2 start_pos, float angle, t_mlx *mlx)
{
	t_ray	*result;

	result = malloc(sizeof(t_ray));
	result->angle = angle;
	result->start_pos = start_pos;
	result->end_pos = ray_get_end_pos(result, start_pos, angle, mlx);
	result->length = ray_get_length(start_pos, result->end_pos);
	if (result->length >= mlx->dov * 100)
	{
		if (result->wall_hit_dir == NORTH || result->wall_hit_dir == SOUTH)
			result->wall_hit_dir = FOG_NORTH_SOUTH;
		else
			result->wall_hit_dir = FOG_EAST_WEST;
	}
	result->next_ray = NULL;
	return (result);
}

void	draw_ray(t_vector2 start_pos, t_ray *ray, t_mlx *mlx)
{
	t_vector2	diff;
	t_vector2	mul_vec;
	t_vector2	ray_pos_in_map;
	t_vector2	ray_end_pos_in_map;

	// printf("ray start pos = (%d, %d)\n", ray->start_pos.x, ray->start_pos.y);
	// printf("ray end pos = (%d, %d)\n", ray->end_pos.x, ray->end_pos.y);
	diff = sub_vec2(ray->end_pos, ray->start_pos);
	mul_vec = div_vec2(vec2(100, 100), mlx->cube_size_minimap);
	ray_end_pos_in_map = div_vec2(diff, mul_vec);
	ray_pos_in_map = add_vec2(start_pos, ray_end_pos_in_map);
	// printf("ray start pos = (%d, %d)\n", start_pos.x, start_pos.y);
	// printf("ray end pos = (%d, %d)\n", ray_pos_in_map.x, ray_pos_in_map.y);
	clamp_vec2(&ray_pos_in_map, vec2(0, 0), mlx->minimap_size);
	ray_pos_in_map = add_vec2(ray_pos_in_map, mlx->minimap_margin);
	draw_line(&mlx->imgs[0], add_vec2(start_pos, mlx->minimap_margin), ray_pos_in_map, 0xFF0000);
}

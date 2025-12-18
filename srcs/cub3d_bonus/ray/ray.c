/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpecquer <jpecquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:18:41 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/18 23:47:15 by jpecquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

t_vector2	ray_check_loop(float rx, float ry, t_mlx *mlx, int dov)
{
	int	grid_x;
	int	grid_y;

	while (is_out_of_bounds(div_vec2(vec2((int)rx, (int)ry), vec2(100, 100)),
			mlx->board_size) == FALSE)
	{
		grid_x = (int)(rx / 100);
		grid_y = (int)(ry / 100);
		if (mlx->board[grid_y][grid_x] == '1' || dov >= mlx->dov ||
			mlx->board[grid_y][grid_x] == 'F')
			break ;
		rx += mlx->ox;
		ry += mlx->oy;
		dov++;
	}
	return (vec2((int)rx, (int)ry));
}

t_vector2	ray_check_horizontal_lines(t_vector2 start_pos, float angle,
		t_mlx *mlx)
{
	float	a_tan;
	float	ry;
	float	rad;
	float	rx;
	int		dov;

	dov = 0;
	rad = (angle * M_PI) / 180;
	a_tan = -1 / tan(rad);
	ry = start_pos.y;
	if (rad > M_PI)
	{
		ry -= (int)ry % 100 + 0.001;
		rx = (start_pos.y - ry) * a_tan + start_pos.x;
		mlx->oy = -100;
		mlx->ox = (-1 * mlx->oy) * a_tan;
	}
	if (rad <= M_PI)
	{
		ry += (100 - ((int)ry % 100));
		rx = (start_pos.y - ry) * a_tan + start_pos.x;
		mlx->oy = 100;
		mlx->ox = (-1 * mlx->oy) * a_tan;
	}
	return (ray_check_loop(rx, ry, mlx, dov));
}

t_vector2	ray_check_vertical_lines(t_vector2 start_pos, float angle,
		t_mlx *mlx)
{
	float	n_tan;
	float	rad;
	float	ry;
	float	rx;
	int		dov;

	dov = 0;
	rad = (angle * M_PI) / 180;
	n_tan = -1 * tan(rad);
	rx = start_pos.x;
	if (rad <= (M_PI / 2) || rad >= (3 * M_PI / 2))
	{
		rx += 100 - ((int)rx % 100);
		ry = (start_pos.x - rx) * n_tan + start_pos.y;
		mlx->ox = 100;
		mlx->oy = (-1 * mlx->ox) * n_tan;
	}
	if (rad > (M_PI / 2) && rad < (3 * M_PI / 2))
	{
		rx -= ((int)rx % 100) + 0.01;
		ry = (start_pos.x - rx) * n_tan + start_pos.y;
		mlx->ox = -100;
		mlx->oy = (-1 * mlx->ox) * n_tan;
	}
	return (ray_check_loop(rx, ry, mlx, dov));
}

t_vector2	ray_get_end_pos(t_ray *ray, t_vector2 start_pos, float angle,
		t_mlx *mlx)
{
	t_vector2	horizontal_lines;
	t_vector2	vertical_lines;
	float		h_length;
	float		v_length;

	horizontal_lines = ray_check_horizontal_lines(start_pos, angle, mlx);
	vertical_lines = ray_check_vertical_lines(start_pos, angle, mlx);
	v_length = ray_get_length(start_pos, vertical_lines);
	h_length = ray_get_length(start_pos, horizontal_lines);
	if ((v_length <= h_length && (int)v_length > 0) || (int)h_length <= 0)
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

void	draw_ray(t_vector2 start_pos, t_ray *ray, t_mlx *mlx)
{
	t_vector2	diff;
	t_vector2	mul_vec;
	t_vector2	ray_pos_in_map;
	t_vector2	ray_end_pos_in_map;

	diff = sub_vec2(ray->end_pos, ray->start_pos);
	mul_vec = div_vec2(vec2(100, 100), mlx->cube_size_minimap);
	ray_end_pos_in_map = div_vec2(diff, mul_vec);
	ray_pos_in_map = add_vec2(start_pos, ray_end_pos_in_map);
	clamp_vec2(&ray_pos_in_map, vec2(0, 0), mlx->minimap_size);
	ray_pos_in_map = add_vec2(ray_pos_in_map, mlx->minimap_margin);
	draw_line(&mlx->imgs[0], add_vec2(start_pos, mlx->minimap_margin),
		ray_pos_in_map, 0xFF0000);
}

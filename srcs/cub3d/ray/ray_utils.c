/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpecquer <jpecquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:25:36 by dfeve             #+#    #+#             */
/*   Updated: 2026/01/12 15:35:18 by jpecquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

char	get_cell(int x, int y, t_mlx *mlx)
{
	if (x < 0 || y < 0 || x >= mlx->board_size.x || y >= mlx->board_size.y)
		return ('1');
	return (mlx->board[y][x]);
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
	if (get_cell(result->end_pos.x / 100, result->end_pos.y / 100, mlx) == 'F')
	{
		if (result->wall_hit_dir == NORTH || result->wall_hit_dir == SOUTH)
			result->wall_hit_dir = DOOR_NORTH_SOUTH;
		else
			result->wall_hit_dir = DOOR_EAST_WEST;
	}
	result->next_ray = NULL;
	return (result);
}

float	wtf_sqrt( float number )
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
	return (result);
}

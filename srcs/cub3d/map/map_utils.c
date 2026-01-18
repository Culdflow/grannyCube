/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:28:56 by dfeve             #+#    #+#             */
/*   Updated: 2026/01/18 00:49:21 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

t_vector2	minimap_get_start_pos(t_data *data)
{
	t_vector2	cube_size_help;
	t_vector2	player_pos_in_map;
	t_vector2	result;

	player_pos_in_map = div_vec2(data->mlx->minimap_size, vec2(2, 2));
	cube_size_help = div_vec2(player_pos_in_map, data->mlx->cube_size_minimap);
	result = vec2(data->player->x - (cube_size_help.x * CUBESIZE),
			data->player->y - (cube_size_help.y * CUBESIZE));
	cube_size_help.x = player_pos_in_map.x % data->mlx->cube_size_minimap.x;
	cube_size_help.y = player_pos_in_map.y % data->mlx->cube_size_minimap.y;
	if (cube_size_help.x != 0)
		cube_size_help.x = CUBESIZE
			/ (data->mlx->cube_size_minimap.x / cube_size_help.x);
	if (cube_size_help.y != 0)
		cube_size_help.y = CUBESIZE
			/ (data->mlx->cube_size_minimap.y / cube_size_help.y);
	result = sub_vec2(result, cube_size_help);
	return (result);
}

void	draw_pixel_minimap(t_vector2 map_pos, t_vector2 pos, t_data *data)
{
	if (map_pos.x <= 0 || map_pos.y <= 0
		|| (map_pos.x / CUBESIZE) >= data->mlx->board_size.x
		|| (map_pos.y / CUBESIZE) >= data->mlx->board_size.y)
		my_mlx_pixel_put(&data->mlx->imgs[0], pos.x, pos.y, 0x00FFFF);
	else if (data->mlx->board && data->mlx->board[map_pos.y / CUBESIZE]
		&& data->mlx->board[map_pos.y / CUBESIZE][map_pos.x / CUBESIZE])
	{
		if (data->mlx->board[map_pos.y / CUBESIZE][map_pos.x / CUBESIZE] == '1')
			my_mlx_pixel_put(&data->mlx->imgs[0], pos.x, pos.y, 0x000000);
		else if (data->mlx->board[map_pos.y / CUBESIZE][map_pos.x / CUBESIZE]
			== '0')
			my_mlx_pixel_put(&data->mlx->imgs[0], pos.x, pos.y, 0xFFFFFF);
		else if (data->mlx->board[map_pos.y / CUBESIZE][map_pos.x / CUBESIZE]
			== ' ')
			my_mlx_pixel_put(&data->mlx->imgs[0], pos.x, pos.y, 0x00FFFF);
		else if (data->mlx->board[map_pos.y / CUBESIZE][map_pos.x / CUBESIZE]
			== 'G')
			my_mlx_pixel_put(&data->mlx->imgs[0], pos.x, pos.y, 0xF05050);
		else
			my_mlx_pixel_put(&data->mlx->imgs[0], pos.x, pos.y, 0xF0F0F0);
	}
}

void	draw_minimap(t_data *data)
{
	t_vector2	map_pos;
	t_vector2	pos;
	int			save_x;

	pos = data->mlx->minimap_margin;
	draw_rectangle_no_fill(&data->mlx->imgs[0], sub_vec2(pos, vec2(1, 1)),
		add_vec2(data->mlx->minimap_margin, add_vec2(data->mlx->minimap_size,
				vec2(1, 1))), 0xFFFFFF);
	map_pos = minimap_get_start_pos(data);
	save_x = map_pos.x;
	while (pos.y <= data->mlx->minimap_size.y + data->mlx->minimap_margin.y)
	{
		pos.x = data->mlx->minimap_margin.x;
		map_pos.x = save_x;
		while (pos.x <= data->mlx->minimap_size.x + data->mlx->minimap_margin.x)
		{
			draw_pixel_minimap(map_pos, pos, data);
			pos.x++;
			map_pos.x += CUBESIZE / data->mlx->cube_size_minimap.x;
		}
		pos.y++;
		map_pos.y += CUBESIZE / data->mlx->cube_size_minimap.y;
	}
}

void	zoom_minimap(t_mlx *mlx, int val)
{
	t_vector2	new_minimap_cube_size;

	new_minimap_cube_size = add_vec2(mlx->cube_size_minimap, vec2(val, val));
	clamp_vec2(&new_minimap_cube_size, vec2(25, 25), vec2(50, 50));
	mlx->cube_size_minimap = new_minimap_cube_size;
}

int	is_out_of_bounds(t_vector2 coord, t_vector2 map_size)
{
	if (coord.x < 0 || coord.y < 0 || coord.x >= map_size.x
		|| coord.y >= map_size.y)
		return (TRUE);
	return (FALSE);
}

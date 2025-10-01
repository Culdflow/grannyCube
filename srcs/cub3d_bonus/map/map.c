/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 02:40:08 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/24 16:32:42 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

t_vector2	get_square_size(t_vector2 screen_size, t_vector2 map_size)
{
	t_vector2	square_size;

	square_size.x = screen_size.x / map_size.x;
	square_size.y = screen_size.y / map_size.y;
	return (square_size);
}

t_vector2	convert_pos_to_map_pos(t_vector2 pos, t_vector2 screen_size, t_vector2 map_size)
{
	t_vector2	square_size;
	t_vector2	result;

	square_size = get_square_size(screen_size, map_size);
	result.x = (pos.x - 20) / square_size.x;
	result.y = (pos.y - 20) / square_size.y;
	return (result);
}

t_vector2	convert_map_pos_to_pos(t_vector2 map_pos, t_vector2 screen_size, t_vector2 map_size)
{
	t_vector2	square_size;
	t_vector2	result;

	square_size = get_square_size(screen_size, map_size);
	result.x = (map_pos.x * square_size.x) + (square_size.x / 2) + 20;
	result.y = (map_pos.y * square_size.y) + (square_size.y / 2) + 20;
	return (result);
}

int	is_coord_in_map(t_vector2 coord, t_vector2 map_size)
{
	if (coord.x <= map_size.x && coord.x >= 0 && coord.y <= map_size.y && coord.y >= 0)
		return (TRUE);
	return (FALSE);
}

t_vector2	minimap_get_start_pos(t_data *data)
{
	t_vector2	cube_size_help;
	t_vector2	player_pos_in_map;
	t_vector2	result;

	player_pos_in_map = div_vec2(data->mlx->minimap_size, vec2(2, 2));
	cube_size_help = div_vec2(player_pos_in_map, data->mlx->cube_size_minimap);
	result = vec2(data->player->x - (cube_size_help.x * 100), data->player->y - (cube_size_help.y * 100));
	cube_size_help.x = player_pos_in_map.x % data->mlx->cube_size_minimap.x;
	cube_size_help.y = player_pos_in_map.y % data->mlx->cube_size_minimap.y;
	if (cube_size_help.x != 0)
		cube_size_help.x = 100 / (data->mlx->cube_size_minimap.x / cube_size_help.x);
	if (cube_size_help.y != 0)
		cube_size_help.y = 100 / (data->mlx->cube_size_minimap.y / cube_size_help.y);
	result = sub_vec2(result, cube_size_help);
	return (result);
}

void	draw_pixel_minimap(t_vector2 map_pos, t_vector2 pos, t_data *data)
{
	if (map_pos.x <= 0 || map_pos.y <= 0 || (map_pos.x / 100) >= data->mlx->board_size.x
			|| (map_pos.y / 100) >= data->mlx->board_size.y)
		my_mlx_pixel_put(&data->mlx->imgs[0], pos.x, pos.y, 0x00FFFF);
	else if (data->mlx->board && data->mlx->board[map_pos.y / 100] && data->mlx->board[map_pos.y / 100][map_pos.x / 100])
	{
		if (data->mlx->board[map_pos.y / 100][map_pos.x / 100] == '1')
			my_mlx_pixel_put(&data->mlx->imgs[0], pos.x, pos.y, 0x000000);
		else if (data->mlx->board[map_pos.y / 100][map_pos.x / 100] == '0')
			my_mlx_pixel_put(&data->mlx->imgs[0], pos.x, pos.y, 0xFFFFFF);
		else if (data->mlx->board[map_pos.y / 100][map_pos.x / 100] == ' ')
			my_mlx_pixel_put(&data->mlx->imgs[0], pos.x, pos.y, 0x00FFFF);
		else if (data->mlx->board[map_pos.y / 100][map_pos.x / 100] == 'G')
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
	draw_rectangle_no_fill(&data->mlx->imgs[0], sub_vec2(pos, vec2(1, 1)), add_vec2(data->mlx->minimap_margin, add_vec2(data->mlx->minimap_size, vec2(1, 1))), 0xFFFFFF);
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
			map_pos.x += 100 / data->mlx->cube_size_minimap.x;
		}
		pos.y++;
		map_pos.y += 100 / data->mlx->cube_size_minimap.y;
	}
}

void	zoom_minimap(t_mlx *mlx, int val)
{
	t_vector2	new_minimap_cube_size;

	new_minimap_cube_size = add_vec2(mlx->cube_size_minimap, vec2(val, val));
	clamp_vec2(&new_minimap_cube_size, vec2(25,25), vec2(50, 50));
	mlx->cube_size_minimap = new_minimap_cube_size;
}

int	is_out_of_bounds(t_vector2 coord, t_vector2 map_size)
{
	if (coord.x < 0 || coord.y < 0 || coord.x >= map_size.x 
		|| coord.y >= map_size.y)
		return (TRUE);
	return (FALSE);
}
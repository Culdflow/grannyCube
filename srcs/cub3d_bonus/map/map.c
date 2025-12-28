/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 02:40:08 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/28 18:43:32 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub3d_bonus.h"

t_vector2	get_square_size(t_vector2 screen_size, t_vector2 map_size)
{
	t_vector2	square_size;

	square_size.x = screen_size.x / map_size.x;
	square_size.y = screen_size.y / map_size.y;
	return (square_size);
}

t_vector2	convert_pos_to_map_pos(t_vector2 pos, t_vector2 screen_size,
				t_vector2 map_size)
{
	t_vector2	square_size;
	t_vector2	result;

	square_size = get_square_size(screen_size, map_size);
	result.x = (pos.x - 20) / square_size.x;
	result.y = (pos.y - 20) / square_size.y;
	return (result);
}

t_vector2	convert_map_pos_to_pos(t_vector2 map_pos, t_vector2 screen_size,
				t_vector2 map_size)
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
	if (coord.x <= map_size.x && coord.x >= 0 && coord.y <= map_size.y
		&& coord.y >= 0)
		return (TRUE);
	return (FALSE);
}

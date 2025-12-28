/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:51:31 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/28 19:14:13 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	look_player(t_player *player, int turning_right)
{
	if (turning_right == TRUE)
		player->angle += player->look_speed;
	else
		player->angle -= player->look_speed;
	if (player->angle < 0)
		player->angle = 360 - abs((int)player->angle);
	player->angle = (int)player->angle % 360;
}

void	look_player_mouse(t_player *player, int mouse_diff)
{
	player->angle += mouse_diff / 10;
	if (player->angle < 0)
		player->angle = 360 - abs((int)player->angle);
	player->angle = (int)player->angle % 360;
}

void	draw_player_view_line(t_player *player, t_mlx *mlx,
		t_vector2 minimap_center)
{
	float			new_x;
	float			new_y;
	float			rad;

	rad = (player->angle * M_PI) / 180;
	new_x = 15 * cos(rad);
	new_y = 15 * sin(rad);
	new_x = minimap_center.x + new_x;
	new_y = minimap_center.y + new_y;
	draw_line(&mlx->imgs[0], minimap_center, vec2(new_x, new_y), 0xc4c0dd);
}

void	draw_player(t_player *player, t_mlx *mlx)
{
	t_vector2	start;
	t_vector2	end;
	t_vector2	minimap_center;

	minimap_center = add_vec2(div_vec2(mlx->minimap_size, vec2(2, 2)),
			mlx->minimap_margin);
	start = sub_vec2(minimap_center, vec2(5, 5));
	end = add_vec2(minimap_center, vec2(5, 5));
	clamp_vec2(&start, vec2(0, 0), mlx->minimap_size);
	clamp_vec2(&end, vec2(0, 0), mlx->minimap_size);
	draw_rectangle(&mlx->imgs[0], start, end, 0x00FF00);
	draw_player_view_line(player, mlx, minimap_center);
}

t_vector2	find_player(char **map)
{
	t_vector2	cursor;

	cursor = vec2(0, 0);
	while (map && map[cursor.y])
	{
		cursor.x = 0;
		while (map[cursor.y][cursor.x])
		{
			if (map[cursor.y][cursor.x] == 'N'
				|| map[cursor.y][cursor.x] == 'S'
				|| map[cursor.y][cursor.x] == 'E'
				|| map[cursor.y][cursor.x] == 'W')
				return (cursor);
			cursor.x++;
		}
		cursor.y++;
	}
	return (vec2(0, 0));
}

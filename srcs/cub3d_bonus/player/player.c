/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 01:36:44 by dfeve             #+#    #+#             */
/*   Updated: 2025/08/21 19:07:55 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

t_player	*new_player(t_vector2 pos, int angle, int speed, int look_speed)
{
	t_player	*result;

	result = malloc(sizeof(t_player));
	result->x = pos.x;
	result->y = pos.y;
	result->angle = angle;
	result->speed = speed;
	result->look_speed = look_speed;
	result->collisions = malloc(sizeof(t_player_collisions));
	result->collisions->last_collision = NORTH;
	return (result);
}

int	is_player_colliding(float new_x, float new_y, t_data *data)
{
	t_vector2	map_pos;

	map_pos = vec2(new_x / 100, new_y / 100);
	clamp_vec2(&map_pos, vec2(0, 0), data->mlx->board_size);
	if (data->mlx->board[map_pos.y][map_pos.x] != '1')
		return (FALSE);
	return (TRUE);
}

void	add_collision_debug(t_data *data, float x, float y, int collision)
{
	float	conv_x;
	float	conv_y;
	t_vector2	minimap_center;
	t_vector2	start;
	t_vector2	end;

	minimap_center = add_vec2(div_vec2(data->mlx->minimap_size, vec2(2, 2)), data->mlx->minimap_margin);
	conv_x = x - data->player->x + minimap_center.x;
	conv_y = y - data->player->y + minimap_center.y;
	start = vec2((int)conv_x - 2, (int)conv_y - 2);
	end = vec2((int)conv_x + 2, (int)conv_y + 2);
	clamp_vec2(&start, vec2(0, 0), data->mlx->minimap_size);
	clamp_vec2(&end, vec2(0, 0), data->mlx->minimap_size);
	if (collision == TRUE)
		add_debug_obj(&data->mlx->debug_lst, new_debug_obj(RECTANGLE, start, end, 0xFF0000));
	else
		add_debug_obj(&data->mlx->debug_lst, new_debug_obj(RECTANGLE, start, end, 0x00FF00));
}

int	player_collision_helper(float new_x, float new_y, t_data *data)
{
	add_collision_debug(data, new_x, new_y, is_player_colliding(new_x, new_y, data));
	return (is_player_colliding(new_x, new_y, data));
}

t_player_collisions	*get_player_collisions(float new_x, float new_y, t_data *data)
{
	t_player_collisions	*result;

	result = malloc(sizeof(t_player_collisions));
	result->middle = is_player_colliding(new_x, new_y, data);
	result->north = player_collision_helper(new_x, new_y - 20, data);
	result->north_east = player_collision_helper(new_x + 20, new_y - 20, data);
	result->east = player_collision_helper(new_x + 20, new_y, data);
	result->south_east = player_collision_helper(new_x + 20, new_y + 20, data);
	result->south = player_collision_helper(new_x, new_y + 20, data);
	result->south_west = player_collision_helper(new_x - 20, new_y + 20, data);
	result->west = player_collision_helper(new_x - 20, new_y, data);
	result->north_west = player_collision_helper(new_x - 20, new_y - 20, data);
	result->helper_east_north = player_collision_helper(new_x + 20, new_y - 10, data);
	result->helper_east_south = player_collision_helper(new_x + 20, new_y + 10, data);
	result->helper_north_east = player_collision_helper(new_x + 10, new_y - 20, data);
	result->helper_north_west = player_collision_helper(new_x - 10, new_y - 20, data);
	result->helper_south_east = player_collision_helper(new_x + 10, new_y + 20, data);
	result->helper_south_west = player_collision_helper(new_x - 10, new_y + 20, data);
	result->helper_west_north = player_collision_helper(new_x - 20, new_y - 10, data);
	result->helper_west_south = player_collision_helper(new_x - 20, new_y + 10, data);
	result->last_collision = data->player->collisions->last_collision;
	free(data->player->collisions);
	return (result);
}

t_vector2	is_player_colliding_secure(float new_x, float new_y, t_data *data)
{
	t_vector2	result;

	data->player->collisions = get_player_collisions(new_x, new_y, data);
	result = vec2(FALSE, FALSE);
	if (data->player->collisions->north || data->player->collisions->south
		|| data->player->collisions->helper_north_east || data->player->collisions->helper_north_west
		|| data->player->collisions->helper_south_east || data->player->collisions->helper_south_west)
	{
		result.y = TRUE;
		data->player->collisions->last_collision = NORTH;
	}
	if (data->player->collisions->east || data->player->collisions->west
		|| data->player->collisions->helper_east_north || data->player->collisions->helper_east_south
		|| data->player->collisions->helper_west_north || data->player->collisions->helper_west_south)
	{
		result.x = TRUE;
		data->player->collisions->last_collision = EAST;
	}
	if (data->player->collisions->north_east || data->player->collisions->north_west || data->player->collisions->south_east || data->player->collisions->south_west)
	{
		if (data->player->collisions->last_collision == NORTH)
			result.y = TRUE;
		else
			result.x = TRUE;
	}
	return (result);
}

void	move_player(t_player *player, t_vector2 mv_vector, t_data *data)
{
	t_vector2		is_colliding_secure;
	float			new_x;
	float			new_y;
	float			rad;

	rad = (player->angle * M_PI) / 180;
	if (mv_vector.x != 0)
		rad = ((player->angle + 90) * M_PI) / 180;
	if ((mv_vector.x < 0 && mv_vector.y < 0) || (mv_vector.x > 0 && mv_vector.y > 0))
		rad = ((player->angle + 45) * M_PI) / 180;
	if ((mv_vector.x < 0 && mv_vector.y > 0) || (mv_vector.x > 0 && mv_vector.y < 0))
		rad = ((player->angle - 45) * M_PI) / 180;
	new_x = player->speed * cos(rad);
	new_y = player->speed * sin(rad);
	if ((mv_vector.y >= 0 && mv_vector.x >= 0) || compare_vec2(mv_vector, vec2(-1, 1)))
	{
		new_x += player->x;
		new_y += player->y;
	}
	else
	{
		new_x = player->x - new_x;
		new_y = player->y - new_y;
	}
	is_colliding_secure = is_player_colliding_secure(new_x, new_y, data);
	if (is_colliding_secure.x == FALSE)
		player->x = new_x;
	if (is_colliding_secure.y == FALSE)
		player->y = new_y;
}

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

void	draw_player_view_line(t_player *player, t_mlx *mlx, t_vector2 minimap_center)
{
	float			new_x;
	float			new_y;
	float			rad;

	rad = (player->angle * M_PI) / 180;
	new_x = 15 * cos(rad);
	new_y = 15 * sin(rad);
	new_x = minimap_center.x + new_x;
	new_y = minimap_center.y + new_y;
	draw_line(&mlx->imgs[0],minimap_center, vec2(new_x, new_y), 0xc4c0dd);
}

void	draw_player(t_player *player, t_mlx *mlx)
{
	t_vector2	start;
	t_vector2	end;
	t_vector2	minimap_center;

	minimap_center = add_vec2(div_vec2(mlx->minimap_size, vec2(2, 2)), mlx->minimap_margin);
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
				{printf("player found at pos (%d, %d)\n", cursor.x, cursor.y);
				return (cursor);}
			cursor.x++;
		}
		cursor.y++;
	}
	return (vec2(0, 0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:54:31 by dfeve             #+#    #+#             */
/*   Updated: 2026/01/17 22:31:30 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub3d_bonus.h"

void	set_new_var(t_vector2 mv_vector, float *new_x, float *new_y,
			t_player *player)
{
	if ((mv_vector.y >= 0 && mv_vector.x >= 0) || compare_vec2(mv_vector,
			vec2(-1, 1)))
	{
		*new_x += player->x;
		*new_y += player->y;
	}
	else
	{
		*new_x = player->x - *new_x;
		*new_y = player->y - *new_y;
	}
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
	if ((mv_vector.x < 0 && mv_vector.y < 0) || (mv_vector.x > 0
			&& mv_vector.y > 0))
		rad = ((player->angle + 45) * M_PI) / 180;
	if ((mv_vector.x < 0 && mv_vector.y > 0) || (mv_vector.x > 0
			&& mv_vector.y < 0))
		rad = ((player->angle - 45) * M_PI) / 180;
	new_x = player->speed * cos(rad);
	new_y = player->speed * sin(rad);
	set_new_var(mv_vector, &new_x, &new_y, player);
	is_colliding_secure = is_player_colliding_secure(new_x, new_y, data);
	if (is_colliding_secure.x == FALSE)
		player->x = new_x;
	if (is_colliding_secure.y == FALSE)
		player->y = new_y;
}

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

	map_pos = vec2(new_x / CUBESIZE, new_y / CUBESIZE);
	clamp_vec2(&map_pos, vec2(0, 0), data->mlx->board_size);
	if (data->mlx->board[map_pos.y][map_pos.x] != '1'
		&& data->mlx->board[map_pos.y][map_pos.x] != 'F')
		return (FALSE);
	return (TRUE);
}

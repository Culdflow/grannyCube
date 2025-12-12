/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 01:36:44 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/12 22:57:35 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	is_player_colliding(float new_x, float new_y, t_data *data)
{
	t_vector2	map_pos;

	map_pos = vec2(new_x / 100, new_y / 100);
	clamp_vec2(&map_pos, vec2(0, 0), data->mlx->board_size);
	if (data->mlx->board[map_pos.y][map_pos.x] != '1'
		&& data->mlx->board[map_pos.y][map_pos.x] != 'F')
		return (FALSE);
	return (TRUE);
}

void	add_collision_debug(t_data *data, float x, float y, int collision)
{
	float		conv_x;
	float		conv_y;
	t_vector2	minimap_center;
	t_vector2	start;
	t_vector2	end;

	minimap_center = add_vec2(div_vec2(data->mlx->minimap_size,
				vec2(2, 2)), data->mlx->minimap_margin);
	conv_x = x - data->player->x + minimap_center.x;
	conv_y = y - data->player->y + minimap_center.y;
	start = vec2((int)conv_x - 2, (int)conv_y - 2);
	end = vec2((int)conv_x + 2, (int)conv_y + 2);
	clamp_vec2(&start, vec2(0, 0), data->mlx->minimap_size);
	clamp_vec2(&end, vec2(0, 0), data->mlx->minimap_size);
	if (collision == TRUE)
		add_debug_obj(&data->mlx->debug_lst, new_debug_obj(RECTANGLE,
				start, end, 0xFF0000));
	else
		add_debug_obj(&data->mlx->debug_lst, new_debug_obj(RECTANGLE,
				start, end, 0x00FF00));
}

int	player_collision_helper(float new_x, float new_y, t_data *data)
{
	add_collision_debug(data, new_x, new_y, is_player_colliding(new_x,
			new_y, data));
	return (is_player_colliding(new_x, new_y, data));
}

t_player_collisions	*get_player_collisions(float new_x, float new_y,
		t_data *data)
{
	t_player_collisions	*result;

	result = malloc(sizeof(t_player_collisions));
	result->middle = is_player_colliding(new_x, new_y, data);
	result->n = player_collision_helper(new_x, new_y - 20, data);
	result->n_e = player_collision_helper(new_x + 20, new_y - 20, data);
	result->e = player_collision_helper(new_x + 20, new_y, data);
	result->s_e = player_collision_helper(new_x + 20, new_y + 20, data);
	result->s = player_collision_helper(new_x, new_y + 20, data);
	result->s_w = player_collision_helper(new_x - 20, new_y + 20, data);
	result->w = player_collision_helper(new_x - 20, new_y, data);
	result->n_w = player_collision_helper(new_x - 20, new_y - 20, data);
	result->helper_e_n = player_collision_helper(new_x + 20, new_y - 10, data);
	result->helper_e_s = player_collision_helper(new_x + 20, new_y + 10, data);
	result->helper_n_e = player_collision_helper(new_x + 10, new_y - 20, data);
	result->helper_n_w = player_collision_helper(new_x - 10, new_y - 20, data);
	result->helper_s_e = player_collision_helper(new_x + 10, new_y + 20, data);
	result->helper_s_w = player_collision_helper(new_x - 10, new_y + 20, data);
	result->helper_w_n = player_collision_helper(new_x - 20, new_y - 10, data);
	result->helper_w_s = player_collision_helper(new_x - 20, new_y + 10, data);
	result->last_collision = data->player->collisions->last_collision;
	free(data->player->collisions);
	return (result);
}

t_vector2	is_player_colliding_secure(float new_x, float new_y, t_data *data)
{
	t_vector2			result;
	t_player_collisions	*p_co;

	data->player->collisions = get_player_collisions(new_x, new_y, data);
	p_co = data->player->collisions;
	result = vec2(FALSE, FALSE);
	if (p_co->n || p_co->s || p_co->helper_n_e || p_co->helper_n_w
		|| p_co->helper_s_e || p_co->helper_s_w)
	{
		result.y = TRUE;
		data->player->collisions->last_collision = NORTH;
	}
	if (p_co->e || p_co->w || p_co->helper_e_n || p_co->helper_e_s
		|| p_co->helper_w_n || p_co->helper_w_s)
	{
		result.x = TRUE;
		data->player->collisions->last_collision = EAST;
	}
	if (p_co->n_e || p_co->n_w || p_co->s_e || p_co->s_w)
	{
		if (p_co->last_collision != NORTH)
			result.x = TRUE;
	}
	return (result);
}

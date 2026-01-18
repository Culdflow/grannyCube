/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:51:31 by jpecquer          #+#    #+#             */
/*   Updated: 2026/01/18 02:09:05 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub3d_bonus.h"

void	load_textures(t_data *data)
{
	int			h;
	int			w;
	t_vector2	spawn_point;
	int			angle;

	if (data->player_angle == 'S')
		angle = 270;
	else if (data->player_angle == 'W')
		angle = 180;
	else if (data->player_angle == 'N')
		angle = 90;
	else
		angle = 0;
	mlx_get_screen_size(data->mlx->mlx, &w, &h);
	data->height = h;
	data->width = w;
	spawn_point = add_vec2(mul_vec2(find_player(data->mlx->board),
				vec2(CUBESIZE, CUBESIZE)), vec2(CUBESIZE / 2 + 2,
				CUBESIZE / 2 - 1));
	data->player = new_player(spawn_point, angle, 5, 5);
}

static void	step_check_keys(t_data *data)
{
	if (data->keys[K_AR_D] == TRUE)
		zoom_minimap(data->mlx, 25);
	if (data->keys[K_AR_U] == TRUE)
		zoom_minimap(data->mlx, -25);
	if (data->keys[K_AR_L] == TRUE)
		look_player(data->player, FALSE);
	if (data->keys[K_AR_R] == TRUE)
		look_player(data->player, TRUE);
	if (data->keys[K_J] == TRUE)
		switch_anim(data->mlx->hud_char, "state_1");
	if (data->keys[K_K] == TRUE)
		switch_anim(data->mlx->hud_char, "state_2");
	if (data->keys[K_L] == TRUE)
		switch_anim(data->mlx->hud_char, "state_3");
}

void	check_keys(t_data *data)
{
	t_vector2	mv_vec;

	mv_vec = vec2(0, 0);
	if (data->keys[K_W] == TRUE)
		mv_vec.y += 1;
	if (data->keys[K_S] == TRUE)
		mv_vec.y += -1;
	if (data->keys[K_A] == TRUE)
		mv_vec.x += -1;
	else if (data->keys[K_D] == TRUE)
		mv_vec.x += 1;
	if (!compare_vec2(mv_vec, vec2(0, 0)))
		move_player(data->player, mv_vec, data);
	step_check_keys(data);
	if (data->keys[K_E] == TRUE)
		data->mlx->is_interracting = TRUE;
	else
		data->mlx->is_interracting = FALSE;
}

static void	step_check_door(t_data *data, float new_x, float new_y)
{
	if (data->mlx->board[(int)new_y / CUBESIZE][(int)new_x / CUBESIZE] == 'O')
		data->mlx->board[(int)new_y / CUBESIZE][(int)new_x / CUBESIZE] = 'F';
	else
		data->mlx->board[(int)new_y / CUBESIZE][(int)new_x / CUBESIZE] = 'O';
	data->mlx->is_interracting = FALSE;
	data->keys[K_E] = FALSE;
}

void	check_door(t_data *data)
{
	float	rad;
	float	new_x;
	float	new_y;
	int		dist;

	dist = CUBESIZE;
	new_x = 0;
	new_y = 0;
	rad = (data->player->angle * M_PI) / 180;
	while (dist <= CUBESIZE * 2 && data->mlx->board)
	{
		new_x = dist * cos(rad);
		new_y = dist * sin(rad);
		new_x += data->player->x;
		new_y += data->player->y;
		if ((data->mlx->board[(int)new_y / CUBESIZE][(int)new_x / CUBESIZE]
			== 'O'
			|| data->mlx->board[(int)new_y / CUBESIZE][(int)new_x / CUBESIZE]
				== 'F')
			&& data->mlx->is_interracting)
		{
			step_check_door(data, new_x, new_y);
		}
		dist += CUBESIZE;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpecquer <jpecquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:40:18 by jpecquer          #+#    #+#             */
/*   Updated: 2025/12/17 22:16:50 by jpecquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	on_keypress(int keysym, t_data *data)
{
	if (keysym == K_ESC)
		free_data(data);
	else if (keysym < 65365)
		data->keys[keysym] = TRUE;
	return (0);
}

int	on_keyrelease(int keysym, t_data *data)
{
	if (keysym < 65365)
		data->keys[keysym] = FALSE;
	return (0);
}

void	mouse_pos(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(data->mlx->mlx, data->mlx->win, &x, &y);
	data->mouseX = x;
	if (data->mouseX < 10)
	{
		mlx_mouse_move(data->mlx->mlx, data->mlx->win,
			data->mlx->screen_size.x - 10, data->mlx->screen_size.y / 2);
	}
	if (data->mouseX > data->mlx->screen_size.x - 10)
	{
		mlx_mouse_move(data->mlx->mlx, data->mlx->win,
			10, data->mlx->screen_size.y / 2);
	}
	look_player_mouse(data->player, data->mouseX - data->old_mouseX);
	if (data->mouseX > data->mlx->screen_size.x - 10)
		data->old_mouseX = 0;
	else if (data->mouseX < 10)
		data->old_mouseX = data->mlx->screen_size.x;
	else
		data->old_mouseX = data->mouseX;
}

void	step_draw_textures(t_data *data, int frame)
{
	data->ray_list = new_ray_list(60, data->player->angle,
			vec2((int)data->player->x, (int)data->player->y), data->mlx);
	draw_floor_ceiling(data, data->mlx->screen_size, data->textures);
	draw_3d_view(data, data->mlx->screen_size);
	draw_minimap(data);
	draw_player(data->player, data->mlx);
	draw_frame(data->mlx->HUD, data->mlx, frame);
	draw_frame(data->mlx->HUD_CHAR->current_anim, data->mlx, frame);
	draw_debug(data->mlx->debug_lst, data->mlx);
	data->mlx->debug_lst = NULL;
	put_imgs(data->mlx);
	free_ray_list(&data->ray_list);
}

int	draw_textures(t_data *data)
{
	static struct timeval	last = {0};
	struct timeval			now;
	double					elapsed;
	static int				frame = 0;

	gettimeofday(&now, NULL);
	elapsed = (now.tv_sec - last.tv_sec) + (now.tv_usec - last.tv_usec)
		/ 1000000.0;
	if (elapsed < 1.0 / 30.0)
		return (0);
	frame++;
	frame = frame % 30;
	data->player->speed = elapsed * 200;
	last = now;
	del_images(data->mlx);
	check_keys(data);
	check_door(data);
	mouse_pos(data);
	new_image(data->mlx, data->mlx->screen_size, vec2(0, 0));
	step_draw_textures(data, frame);
	data->ray_list = NULL;
	return (0);
}

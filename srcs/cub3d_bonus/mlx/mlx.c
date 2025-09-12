/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 23:23:41 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/12 04:21:08 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

t_mlx	*setup_mlx(char *name, t_vector2 minimap_size)
{
	t_mlx	*mlx;
	t_vector2 screen_size;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (NULL);
	mlx_get_screen_size(mlx->mlx, &screen_size.x, &screen_size.y);
	mlx->win = mlx_new_window(mlx->mlx, screen_size.x, screen_size.y, name);
	mlx->imgs[0].img = NULL;
	mlx->is_clicking = FALSE;
	mlx->screen_size = screen_size;
	mlx->board = NULL;
	mlx->obj_list = NULL;
	mlx->minimap_size = minimap_size;
	mlx->cube_size_minimap = vec2(50, 50);
	mlx->minimap_margin = vec2(30, 50);
	mlx->debug_lst = NULL;
	hud_char(mlx);
	mlx->HUD = hud(mlx);
	mlx->dov = 3;
	return (mlx);
}

void	free_mlx(t_mlx *mlx)
{
	if (mlx->board)
		free_tab(mlx->board, mlx->board_size);
	free_object_list(mlx->obj_list);
	del_images(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx);
}

t_vector2	get_map_size(char **map)
{
	t_vector2	cursor;
	t_vector2	result;

	cursor = vec2(0, 0);
	result = vec2(0, 0);
	while (map && map[cursor.y])
	{
		cursor.x = 0;
		while (map[cursor.y][cursor.x])
			cursor.x++;
		if (cursor.x > result.x)
			result.x = cursor.x;
		cursor.y++;
	}
	result.y = cursor.y;
	return (result);
}

void	setup_data(t_data *data)
{
	int	i;

	i = 0;
	data->ray_list = NULL;
	while (data->keys[i])
	{
		data->keys[i] = FALSE;
		i++;
	}
}
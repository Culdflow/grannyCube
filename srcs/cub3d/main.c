/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:26:04 by mabdessm          #+#    #+#             */
/*   Updated: 2025/12/28 19:13:59 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	init_data(t_data *data, char *file)
{
	data->number_of_no = 0;
	data->number_of_so = 0;
	data->number_of_we = 0;
	data->number_of_ea = 0;
	data->number_of_f = 0;
	data->number_of_c = 0;
	data->number_of_g = 1;
	data->number_of_players = 0;
	data->invalid_floor_color = 0;
	data->path_to_the_north_texture = NULL;
	data->path_to_the_south_texture = NULL;
	data->path_to_the_west_texture = NULL;
	data->path_to_the_east_texture = NULL;
	data->floor_color = NULL;
	data->ceiling_color = NULL;
	data->seperated_floor_color = NULL;
	data->seperated_ceiling_color = NULL;
	data->map = NULL;
	data->mlx->board = check_errors(file, data);
	refill_map(&data->mlx->board);
	data->mlx->board_size = get_map_size(data->mlx->board);
	if (data->mlx->board)
		return (1);
	else
		return (0);
}

static void	free_data_path_texture(t_data *data)
{
	if (data->path_to_the_north_texture)
		free(data->path_to_the_north_texture);
	if (data->path_to_the_south_texture)
		free(data->path_to_the_south_texture);
	if (data->path_to_the_west_texture)
		free(data->path_to_the_west_texture);
	if (data->path_to_the_east_texture)
		free(data->path_to_the_east_texture);
}

int	free_data(t_data *data)
{
	free_data_path_texture(data);
	if (data->floor_color)
		free(data->floor_color);
	if (data->ceiling_color)
		free(data->ceiling_color);
	if (data->seperated_floor_color)
		ft_free_tab(data->seperated_floor_color);
	if (data->seperated_ceiling_color)
		ft_free_tab(data->seperated_ceiling_color);
	if (data->ray_list)
		free_ray_list(&data->ray_list);
	if (data->map)
	{
		ft_free_tab(data->map);
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	}
	free_mlx(data->mlx);
	exit(0);
	return (0);
}

int	start_game(t_data data, char *name)
{
	data.mlx = setup_mlx("cub3d", vec2(250, 200));
	if (!(init_data(&data, name)))
	{
		free(name);
		free_data(&data);
		return (1);
	}
	free(name);
	data.textures = new_textures(rgb_to_hex(data.floor_color),
			rgb_to_hex(data.ceiling_color), &data);
	load_textures(&data);
	setup_hooks(&data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	char		*name;

	setup_data(&data);
	if (argc == 2)
	{
		name = ft_strdup(argv[1]);
		if (start_game(data, name) == 1)
			return (1);
	}
	else
		return (!return_error("Invalid number of arguments!"));
	return (0);
}

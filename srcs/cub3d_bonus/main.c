/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:26:04 by mabdessm          #+#    #+#             */
/*   Updated: 2025/09/12 03:59:01 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

//for testing
void	draw_map(char **map)
{
	int	i;

	i = -1;
	while (map && map[++i])
		printf("%s\n", map[i]);
}

int	init_data(t_data *data, char *file)
{
	data->number_of_no = 0;
	data->number_of_so = 0;
	data->number_of_we = 0;
	data->number_of_ea = 0;
	data->number_of_f = 0;
	data->number_of_c = 0;
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

int	free_data(t_data *data)
{
	if (data->path_to_the_north_texture)
		free(data->path_to_the_north_texture);
	if (data->path_to_the_south_texture)
		free(data->path_to_the_south_texture);
	if (data->path_to_the_west_texture)
		free(data->path_to_the_west_texture);
	if (data->path_to_the_east_texture)
		free(data->path_to_the_east_texture);
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

void	load_textures(t_data *data)
{
	int			h;
	int			w;
	t_vector2	spawn_point;

	mlx_get_screen_size(data->mlx->mlx, &w, &h);
	data->height = h;
	data->width = w;
	spawn_point = add_vec2(mul_vec2(find_player(data->mlx->board), vec2(100, 100)), vec2(50, 50));
	data->player = new_player(spawn_point, 0, 5, 5);
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
	if (data->keys[K_AR_D] == TRUE)
		zoom_minimap(data->mlx, 25);
	if (data->keys[K_AR_U] == TRUE)
		zoom_minimap(data->mlx, -25);
	if (data->keys[K_AR_L] == TRUE)
		look_player(data->player, FALSE);
	if (data->keys[K_AR_R] == TRUE)
		look_player(data->player, TRUE);
	if(data->keys[K_J] == TRUE)
		switch_anim(data->mlx->HUD_CHAR, "state_1");
	if (data->keys[K_K] == TRUE)
		switch_anim(data->mlx->HUD_CHAR, "state_2");
	if (data->keys[K_L] == TRUE)
		switch_anim(data->mlx->HUD_CHAR, "state_3");
}

void	mouse_pos(t_data *data)
{
	int x;
	int y;

	mlx_mouse_get_pos(data->mlx->mlx, data->mlx->win, &x, &y);
	data->mouseX = x;
	if (data->mouseX < 10)
	{
		mlx_mouse_move(data->mlx->mlx, data->mlx->win, data->mlx->screen_size.x - 10, data->mlx->screen_size.y / 2);
		// data->old_mouseX = 0;
	}
	if (data->mouseX > data->mlx->screen_size.x - 10)
	{
		mlx_mouse_move(data->mlx->mlx, data->mlx->win, 10, data->mlx->screen_size.y / 2);
		// data->old_mouseX = data->mlx->screen_size.x;
	}
	look_player_mouse(data->player, data->mouseX - data->old_mouseX);
	if (data->mouseX > data->mlx->screen_size.x - 10)
		data->old_mouseX = 0;
	else if (data->mouseX < 10)
		data->old_mouseX = data->mlx->screen_size.x;
	else
		data->old_mouseX = data->mouseX;
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
	mouse_pos(data);
	new_image(data->mlx, data->mlx->screen_size, vec2(0, 0));
	data->ray_list = new_ray_list(60, data->player->angle, vec2((int)data->player->x, (int)data->player->y), data->mlx);
	draw_floor_ceiling(data, data->mlx->screen_size, data->textures);
	draw_3d_view(data, data->mlx->screen_size);
	draw_minimap(data);
	draw_ray_list(data->ray_list, div_vec2(data->mlx->minimap_size, vec2(2, 2)), data->mlx);
	draw_player(data->player, data->mlx);
	draw_frame(data->mlx->HUD, data->mlx, frame);
	draw_frame(data->mlx->HUD_CHAR->current_anim, data->mlx, frame);
	draw_debug(data->mlx->debug_lst, data->mlx);
	data->mlx->debug_lst = NULL;
	put_imgs(data->mlx);
	free_ray_list(&data->ray_list);
	data->ray_list = NULL;
	return (0);
}

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

void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx->win, ON_KEYDOWN, (1L<<0), on_keypress, data);
	mlx_hook(data->mlx->win, ON_KEYUP, (1L<<1), on_keyrelease, data);
	mlx_hook(data->mlx->win, ON_DESTROY, 0, free_data, data);
	mlx_loop_hook(data->mlx->mlx, draw_textures, data);
	mlx_loop(data->mlx->mlx);
	free_data(data);
}

int	main(int argc, char **argv)
{
	t_data		data;
	//char	*tmp;
	char		*name;

	setup_data(&data);
	if (argc == 1) //for the mandatory part use this main but remove this condition
	{
		name = leveleditor();
		printf("filename = %s\n", name);
		//tmp = ft_strjoin("maps/", name); //add this once we make level editor put it in maps folder
		//free(name);
		//name = tmp;
		//printf("%s", name); //test
	}
	else if (argc == 2)
		name = ft_strdup(argv[1]);
	if (argc == 1 || argc == 2)
	{
		data.mlx = setup_mlx("cub3d", vec2(250, 200));
		if (!(init_data(&data, name)))
		{
			free(name);
			free_data(&data);
		}
		free(name);
		mlx_mouse_hide(data.mlx->mlx, data.mlx->win);
		data.textures = new_textures(rgb_to_hex(data.floor_color), rgb_to_hex(data.ceiling_color), &data);
		load_textures(&data);
		setup_hooks(&data);
	}
	else
		return (!return_error("Invalid number of arguments!"));
}

//TODO
//fix minimap zoom**
//make left and right movement**
//fix player collision**
//make player turn head with mouse movement**

//add ability to go diagonally**
//add security collisions**
//fix collisions so player isnt so close to wall**
//add parsing of color and textures to code**
//fix and finish minimap editor**

//fix leaks
//flip north and west textures

//multiple players in map
//seg_fault when map_error
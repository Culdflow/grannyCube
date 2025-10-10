/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:26:35 by dfeve             #+#    #+#             */
/*   Updated: 2025/10/10 22:43:53 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

char	*file_name_prompt()
{
	char		*name;
	char		*tmp;
	char		*new_tmp;

	name = readline("Name the file: ");
	new_tmp = ft_strjoin("maps/", name);
	free(name);
	name = new_tmp;
	tmp = ft_strjoin(name, ".cub");
	free(name);
	name = tmp;
	return (name);
}

char	**color_prompt()
{
	char			**colors;

	colors = color_choose_window();
	return (colors);
}

char	**texture_prompt()
{
	char	**textures;

	textures = malloc(sizeof(char *) * 5);
	printf("textures are inputed this way: path_to_texture (example: ./textures/north_texture.xpm)\n");
	textures[0] = choose_texture_window("choose north texture", "xpm");
	textures[1] = choose_texture_window("choose south texture", "xpm");
	textures[2] = choose_texture_window("choose east texture", "xpm");
	textures[3] = choose_texture_window("choose west texture", "xpm");
	textures[4] = 0;
	return (textures);
}

void	write_colors_and_textures(int fd, char **colors, char **textures)
{
	ft_putstr_fd("NO ", fd);
	ft_putstr_fd(textures[0], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("EA ", fd);
	ft_putstr_fd(textures[2], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("SO ", fd);
	ft_putstr_fd(textures[1], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("WE ", fd);
	ft_putstr_fd(textures[3], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("F ", fd);
	ft_putstr_fd(colors[0], fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(colors[1], fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(colors[2], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("C ", fd);
	ft_putstr_fd(colors[3], fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(colors[4], fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(colors[5], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("\n", fd);
}

void	write_map(char *filename, char **colors, char **textures, t_mlx *mlx)
{
	char		**tmp_map;
	int			fd;
	t_vector2	cursor;
	t_vector2	map_size;
	
	tmp_map = close_map(mlx->board);
	map_size = mlx->board_size;
	free_mlx(mlx);

	cursor = vec2(0, 0);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write_colors_and_textures(fd, colors, textures);
	while (cursor.y <= map_size.y)
	{
		cursor.x = 0;
		while (cursor.x <= map_size.x)
		{
			write(fd, &tmp_map[cursor.y][cursor.x], 1);
			cursor.x++;
		}
		write(fd, "\n", 1);
		cursor.y++;
	}
	close(fd);
	free_tab(tmp_map, map_size);
}

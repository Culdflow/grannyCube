/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leveleditor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:12 by dfeve             #+#    #+#             */
/*   Updated: 2025/07/31 01:28:21 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

char	*leveleditor(void)
{
	t_mlx		*mlx;
	t_vector2	board_size;
	char		*filename;
	char		**colors;
	char		**textures;

	filename = file_name_prompt();
	colors = color_prompt();
	textures = texture_prompt();
	board_size = map_size_window();
	mlx = editor_window(board_size);
	write_map(filename, colors, textures, mlx);
	free_tab(colors, vec2(0, 2));
	free_tab(textures, vec2(0, 4));
	return (filename);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:14:01 by dfeve             #+#    #+#             */
/*   Updated: 2025/10/01 19:53:18 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	draw_files_window(t_dir_files *files, t_mlx *mlx)
{
	t_dir_files	*cursor;
	int			i;

	i = 0;
	draw_rectangle_no_fill(&mlx->imgs[0], vec2(0, 40), vec2(1500, mlx->screen_size.y - 10), 0x0000FF);
	cursor = files;
	while (files)
	{
		if (files->status == SELECTED)
			draw_rectangle(&mlx->imgs[0], vec2(5, 50 + (i * 20)), vec2(1400, 65 + (i * 20)), 0x588ec4);
		if (files->on_cursor)
			draw_rectangle_no_fill(&mlx->imgs[0], vec2(5, 50 + (i * 20)), vec2(1400, 65 + (i * 20)), 0xFF0000);
		add_obj_to_list(&mlx->obj_list, create_obj(LABEL, NULL, 0, vec2(10, 60 + (i * 20)), vec2(0, 0), 0xFFFFFF, files->name, NULL));
		i++;
		files = files->next;
	}
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
}

char	*choose_texture_window()
{
	t_mlx		*mlx;
	char		*texture;

	texture = NULL;
	mlx = setup_mlx("CHOOSE TEXTURE", vec2(0, 0));
	mlx->files = get_files_from_dir(".");
	new_image(mlx, mlx->screen_size, vec2(0, 0));
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input_file, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, fun_exit, mlx->mlx);
	draw_files_window(mlx->files, mlx);
	mlx_loop(mlx->mlx);
	free_mlx(mlx);
	return (texture);
}
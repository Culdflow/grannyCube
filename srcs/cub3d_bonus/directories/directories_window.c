/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:14:01 by dfeve             #+#    #+#             */
/*   Updated: 2025/10/10 22:47:03 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	draw_files_window(t_dir_files *files, t_mlx *mlx)
{
	t_dir_files	*cursor;
	int			i;

	i = 0;
	draw_rectangle_no_fill(&mlx->imgs[0], vec2(0, 40), vec2(1500, mlx->screen_size.y - 10), 0x0000FF);
	add_obj_to_list(&mlx->obj_list, create_obj(LABEL, NULL, 0, vec2(850, 20), vec2(0, 0), 0xFFFFFF, mlx->dir->prompt, NULL));
	cursor = files;
	while (files)
	{
		if (files->status == SELECTED)
			draw_rectangle(&mlx->imgs[0], vec2(5, 50 + (i * 20)), vec2(1400, 65 + (i * 20)), 0x588ec4);
		if (files->on_cursor)
			draw_rectangle_no_fill(&mlx->imgs[0], vec2(5, 50 + (i * 20)), vec2(1400, 65 + (i * 20)), 0xFF0000);
		if (files->type == T_FILE)
			add_obj_to_list(&mlx->obj_list, create_obj(LABEL, NULL, 0, vec2(10, 60 + (i * 20)), vec2(0, 0), 0xFFFFFF, files->name, NULL));
		else
			add_obj_to_list(&mlx->obj_list, create_obj(LABEL, NULL, 0, vec2(10, 60 + (i * 20)), vec2(0, 0), 0x83d2d6, files->name, NULL));
		i++;
		files = files->next;
	}
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
}

char	*get_texture(t_dir_files *files)
{
	t_dir_files	*cursor;

	cursor = files;
	while (cursor)
	{
		if (cursor->status == SELECTED)
			return (ft_strdup(cursor->name));
		cursor = cursor->next;
	}
	return (NULL);
}

char	*choose_texture_window(char *prompt, char *extension)
{
	t_mlx		*mlx;
	char		*texture;
	char		*tmp;
	char		*tmp2;

	texture = NULL;
	mlx = setup_mlx("CHOOSE TEXTURE", vec2(0, 0));
	mlx->dir = ft_calloc(1, sizeof(t_mlx_dir));
	mlx->dir->extension = ft_strdup(extension);
	mlx->dir->extension_prompt = ft_strjoin("file extension must be ", extension);
	mlx->dir->files = get_files_from_dir(".");
	mlx->dir->cur_dir = ft_strdup(".");
	mlx->dir->prompt = prompt;
	new_image(mlx, mlx->screen_size, vec2(0, 0));
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input_file, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, fun_exit, mlx->mlx);
	draw_files_window(mlx->dir->files, mlx);
	mlx_loop(mlx->mlx);
	texture = get_texture(mlx->dir->files);
	tmp2 = ft_strjoin(mlx->dir->cur_dir, "/");
	tmp = ft_strjoin(tmp2, texture);
	free(tmp2);
	free(texture);
	texture = tmp;
	free_mlx(mlx);
	return (texture);
}
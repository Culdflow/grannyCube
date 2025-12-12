/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:53:10 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/11 22:38:27 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	step_input_file(int keycode, t_dir_files *cursor)
{
	if (keycode == K_AR_D && cursor->next)
	{
		cursor->on_cursor = FALSE;
		cursor->next->on_cursor = TRUE;
		return (1);
	}
	if (keycode == K_AR_U && cursor->prev)
	{
		cursor->on_cursor = FALSE;
		cursor->prev->on_cursor = TRUE;
	}
	return (0);
}

void	do_if_t_directory(t_mlx *mlx, t_dir_files *cursor)
{
	char		*tmp;
	char		*dir;

	tmp = ft_strjoin(mlx->dir->cur_dir, "/");
	dir = ft_strjoin(tmp, cursor->name);
	free(tmp);
	free(mlx->dir->cur_dir);
	mlx->dir->cur_dir = dir;
	free_dir_files(mlx->dir->files);
	mlx->dir->files = get_files_from_dir(dir);
	free_object_list(mlx->obj_list);
	mlx->obj_list = NULL;
}

int	step_two_input_file(t_mlx *mlx, t_dir_files *cursor)
{
	if (check_extension(cursor->name, mlx->dir->extension) == TRUE)
	{
		cursor->status = SELECTED;
		mlx_loop_end(mlx->mlx);
	}
	else
	{
		add_obj_to_list(&mlx->obj_list, create_obj(LABEL, vec2(820, 30),
				0xFF0000, mlx->dir->extension_prompt));
		draw_files_window(mlx->dir->files, mlx);
		return (0);
	}
	return (1);
}

int	step_while_input_file(int keycode, t_mlx *mlx, t_dir_files	*cursor)
{
	while (cursor)
	{
		if (cursor->on_cursor == TRUE)
		{
			if (step_input_file(keycode, cursor) == 1)
				break ;
			if (keycode == K_SP)
			{
				if (cursor->type == T_DIRECTORY)
				{
					do_if_t_directory(mlx, cursor);
					break ;
				}
				else
				{
					if (step_two_input_file(mlx, cursor) == 0)
						return (0);
				}
			}
		}
		cursor = cursor->next;
	}
	return (1);
}

int	_input_file(int keycode, t_mlx *mlx)
{
	t_dir_files	*cursor;

	cursor = mlx->dir->files;
	if (keycode == K_ESC)
		fun_exit(mlx);
	if (step_while_input_file(keycode, mlx, cursor) == 0)
		return (0);
	del_images(mlx);
	new_image(mlx, mlx->screen_size, vec2(0, 0));
	draw_files_window(mlx->dir->files, mlx);
	return (0);
}

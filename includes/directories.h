/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:43:45 by dfeve             #+#    #+#             */
/*   Updated: 2025/10/10 22:45:10 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTORIES_H
# define DIRECTORIES_H

# include <dirent.h>
# include "utils.h"
# include "level_editor.h"
# include "animation.h"

typedef enum	e_file_type
{
	T_FILE,
	T_DIRECTORY,
}	file_type;

typedef enum	e_file_status
{
	NOT_SELECTED,
	SELECTED,
}	file_status;

typedef struct	s_directory_file
{
	file_type				type;
	char					*name;
	file_status				status;
	int						on_cursor;
	struct s_directory_file	*next;
	struct s_directory_file	*prev;
}	t_dir_files;

typedef struct s_mlx_dir
{
	t_dir_files			*files;
	char				*cur_dir;
	char				*prompt;
	char				*extension;
	char				*extension_prompt;
}	t_mlx_dir;


t_dir_files	*get_files_from_dir(char *dir);
char		*choose_texture_window(char *prompt, char *extension);
void		draw_files_window(t_dir_files *files, t_mlx *mlx);
void		free_dir_files(t_dir_files *files);
int			check_get_texture(t_dir_files *files);

int			check_extension(char *filename, char *extension);

#endif
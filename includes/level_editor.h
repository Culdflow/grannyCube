/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_editor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:34 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/12 02:52:31 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVEL_EDITOR_H
# define LEVEL_EDITOR_H
# include "../lib/minilibx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <math.h>
# include <fcntl.h>
# include "utils.h"
# include "../lib/libft/libft.h"
typedef struct s_animation t_animation;
typedef struct s_animation_player t_animation_player;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_vector2	pos;
	t_vector2	size;
}	t_img;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_object_list		*obj_list;
	char				**board;
	int					is_clicking;
	t_vector2			board_size;
	char				turning_to;
	t_img				imgs[50000];
	t_vector2			screen_size;
	t_vector2			minimap_size;
	t_vector2			cube_size_minimap;
	t_vector2			minimap_margin;
	t_debug_obj			*debug_lst;
	t_animation			*HUD;
	t_animation_player	*HUD_CHAR;
	t_vector2			mouse_pos;
	int					dov;
}	t_mlx;

////////////////////////---RENDER---//////////////////////////////////////////

void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
void			draw_rectangle(t_img *data, t_vector2 start, t_vector2 end,
				int color);
void			draw_board(t_mlx *mlx, int color1, char **board,
				t_vector2 board_size);
void			draw_rectangle_no_fill(t_img *data, t_vector2 start,
				t_vector2 end, int color);
void			draw_object_list(t_mlx *mlx, t_object_list *obj_lst);
void			draw_line(t_img *data, t_vector2 start, t_vector2 end, int color);
unsigned int	get_pixel_img(t_img img, int x, int y);

////////////////////////---IMAGES---//////////////////////////////////////////

void			del_images(t_mlx *mlx);
void			add_image(t_mlx *mlx, t_img img);
int				count_images(t_mlx *mlx);
void			put_imgs(t_mlx *mlx);
int				xpm_file_to_img_lst(t_mlx *mlx, char *path, t_vector2 pos);
t_img			*xpm_file_to_img(t_mlx *mlx, char *path, t_vector2 pos);
int				new_image(t_mlx *mlx, t_vector2 size, t_vector2 pos);
void			put_img_to_img(t_img *dst, t_img src, int x, int y);
t_vector2		get_pos_mouse(t_mlx *mlx);
void			draw_image_scaled(t_img *img, float scale, t_vector2 pos, t_mlx *mlx);

////////////////////---THE MOTHERFUCKER HIMSELF---////////////////////////////

char			*leveleditor(void);
char			*file_name_prompt(void);
char			**color_prompt(void);
char			**texture_prompt(void);
void			write_map(char *filename, char **colors, char **textures, t_mlx *mlx);

////////////////////---SIGNALS---////////////////////////////

void			modif_label_up(void *obj_lst, int new_value);
void			modif_label_down(void *obj_lst, int new_value);
void			mlx_loop_end_signal(void *vmlx, int new_value);
int				fun_exit(t_mlx *mlx);

////////////////////---WINDOWS---////////////////////////////

t_vector2		map_size_window(void);
t_mlx			*editor_window(t_vector2 board_size);
char			**color_choose_window();

////////////////////---INPUTS---////////////////////////////

int				_input(int keycode, void *void_mlx);
int				_input_mouse(int x, int y, t_mlx *mlx);
int 			_input_mouse_ex(int x, int y, t_mlx *mlx);
int				_input_mouse_board(int keycode, int x, t_mlx *mlx);
int				_input_mouse_click_down(int keycode, int x, int y, void *void_mlx);
int				_input_mouse_click_up(int keycode, int x, int y, void *void_mlx);
int				_input_mouse_click_up_ex(int keycode, int x, int y, t_mlx *mlx);
int				_input_mouse_click_down_ex(int keycode, int x, int y, t_mlx *mlx);

#endif
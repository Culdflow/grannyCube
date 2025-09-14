/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 05:34:38 by mabdessm          #+#    #+#             */
/*   Updated: 2025/09/14 23:25:34 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>
# include "level_editor.h"
# include "utils.h"
# include "animation.h"
# define M_2PI M_PI / 2
# define M_3PI 3 * M_PI / 2
# define FOG_TEXT "textures/fog_texture.xpm"

typedef enum	directions
{
	NORTH,
	EAST,
	WEST,
	SOUTH,
	FOG_NORTH_SOUTH,
	FOG_EAST_WEST
}	e_dir;

typedef struct	s_player_collisions
{
	int		north_east;
	int		helper_north_east;
	int		helper_east_north;
	int		north;
	int		north_west;
	int		helper_north_west;
	int		helper_west_north;
	int		middle;
	int		west;
	int		east;
	int		south;
	int		south_east;
	int		helper_south_east;
	int		helper_east_south;
	int		south_west;
	int		helper_south_west;
	int		helper_west_south;
	e_dir	last_collision;
}	t_player_collisions;

typedef struct	s_player
{
	float				x;
	float				y;
	float				angle;
	int					speed;
	int					look_speed;
	t_player_collisions	*collisions;
}	t_player;


typedef struct	s_ray
{
	t_vector2		start_pos;
	t_vector2		end_pos;
	float			angle;
	float			length;
	e_dir			wall_hit_dir;
	struct s_ray	*next_ray;
}	t_ray;


typedef struct s_ray_list
{
	int		fov;
	t_ray	*ray_list;
}	t_ray_list;


typedef struct s_textures
{
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	t_img			*north_texture;
	t_img			*south_texture;
	t_img			*east_texture;
	t_img			*west_texture;
	t_img			*fog_texture;
}	t_textures;

typedef struct	s_entity
{
	t_vector2	pos;
	int			hp;
	t_img		sprite;
}	t_entity;

typedef struct s_billboard
{
	t_animation_player	*player;
	t_vector2			pos;
}	t_billboard;


typedef struct s_data
{
	char		**map;
	t_mlx		*mlx;
	int			height;
	int			width;
	char		*path_to_the_north_texture;
	char		*path_to_the_south_texture;
	char		*path_to_the_west_texture;
	char		*path_to_the_east_texture;
	char		*floor_color;
	char		*ceiling_color;
	int			invalid_floor_color;
	char		**seperated_floor_color;
	char		**seperated_ceiling_color;
	int			number_of_no;
	int			number_of_so;
	int			number_of_we;
	int			number_of_ea;
	int			number_of_f;
	int			number_of_c;
	int			number_of_players;
	t_player	*player;
	t_ray_list	*ray_list;
	t_textures	*textures;
	int			keys[65365];
	float		mouseX;
	float		old_mouseX;
}				t_data;

////////////////////////---PARSING---//////////////////////////////////////////

void			draw_map(char **map);		//temp for testing

int				return_error(char *str);
int				invalid_file(char *str);
char			**file_errors(int fd, char *file);
int				empty_lines_in_map(char *buffer);
void			more_error_messages(t_data *data);
void			double_free(char *str1, char *str2);
void			ft_free_tab(char **str);
int				invalid_character(char c);
int				duplicate_player(char c, t_data *data);
unsigned int	longest_line(char **map);
int				no_element(t_data *data);
char			**buffer_errors(char *buffer, t_data *data);
int				ft_isdigit(int c);
int				ft_strstrlen(char **str);
int				color_valid_to_atoi(char *str);
char			*get_map(char *file, t_data *data);
char			**return_null_error(void);
char			**return_check_file_errors(char	**map, t_data *data);
char			**check_file_errors(int fd, t_data *data);
int				check_ceiling_color(t_data *data, char *str);
char			*extract_color(char *file, int *i, int *counter,
					char **destination);
int				invalid_element1(t_data *data, char *file, int *i, char c);
int				invalid_element2(t_data *data, char *file, int *i, char c);
int				is_valid_element(char *file, int *i);
char			*parse_elements(char *file, t_data *data, int *i);
int				map_not_closed(char **map);
void			fill_map(char **new_map, char **map);
int				ft_atoi(const char *nptr);
char			*extract_texture_path(char *file, int *i, int *counter,
					char **dest);
int				no_map_errors(char **map, t_data *data);
int				check_floor_color(t_data *data, char *str);
int				valid_color(t_data *data, char *str, int x);
int				valid_colors(t_data *data);
char			**check_errors(char *file, t_data *data);
char			**close_map(char **map);
void			refill_map(char ***map_ptr);

//////////////////--MLX--////////////////////////////

void			free_mlx(t_mlx *mlx);
t_mlx			*setup_mlx(char *name, t_vector2 minimap_size);
t_vector2		get_map_size(char **map);

//////////////////--PLAYER--////////////////////////////

t_player		*new_player(t_vector2 pos, int angle, int speed, int look_speed);
void			move_player(t_player *player, t_vector2 mv_vector, t_data *data);
void			look_player(t_player *player, int turning_right);
void			draw_player(t_player *player, t_mlx *mlx);
t_vector2		find_player(char **map);
void			look_player_mouse(t_player *player, int mouse_diff);

//////////////////--MAP--////////////////////////////

t_vector2		convert_pos_to_map_pos(t_vector2 pos, t_vector2 screen_size, t_vector2 map_size);
t_vector2		convert_map_pos_to_pos(t_vector2 map_pos, t_vector2 screen_size, t_vector2 map_size);
void			draw_minimap(t_data *data);
void			zoom_minimap(t_mlx *mlx, int val);
int				is_out_of_bounds(t_vector2 coord, t_vector2 map_size);

//////////////////--DATA--////////////////////////////

void			setup_data(t_data *data);

//////////////////--RAY--////////////////////////////

t_ray			*new_ray(t_vector2 start_pos, float angle, t_mlx *mlx);
void			draw_ray(t_vector2 start_pos, t_ray *ray, t_mlx *mlx);
t_ray_list		*new_ray_list(int fov, int base_angle, t_vector2 start_pos, t_mlx *mlx);
void			draw_ray_list(t_ray_list *ray_list, t_vector2 start_pos, t_mlx *mlx);
void			free_ray_list(t_ray_list **ray_list);

//////////////////--VIEW--////////////////////////////

void			draw_floor_ceiling(t_data *data, t_vector2 screen_size, t_textures *textures);
void			draw_3d_view(t_data *data, t_vector2 screen_size);

//////////////////--TEXTURES--////////////////////////////

t_textures		*new_textures(unsigned int floor_color, unsigned int ceiling_color, t_data *data);
void			free_textures(t_textures **textures, t_mlx *mlx);

//////////////////--DEBUG--////////////////////////////

void			draw_debug(t_debug_obj *lst, t_mlx *mlx);

//////////////////--BILLBOARD--////////////////////////

int				trig_get_angle(int adj, int hyp);
int				check_is_angle_in_player_view(int angle, int fov, int player_angle);
float			get_percent_billboard_from_view(int angle, int fov, int player_angle);

t_object		*new_slider(t_vector2 pos, int size, int color, t_mlx *mlx);
#endif
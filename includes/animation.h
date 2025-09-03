/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:55:30 by dfeve             #+#    #+#             */
/*   Updated: 2025/08/28 17:49:33 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include "utils.h"
# include "level_editor.h"

typedef struct s_mlx t_mlx;

typedef struct	s_frame
{
	t_img			*frame;
	int				frame_nb;
	struct s_frame	*current_frame;
	struct s_frame	*next;
}	t_frame;

typedef struct s_animation
{
	char				*anim_tag;
	t_frame				*frames;
	int					anim_play_time;
	int					loop;
	int					next_frame;
	struct s_animation	*next;
}	t_animation;

typedef struct	s_animation_player
{
	t_animation	*current_anim;
	t_animation	*anim_list;
	t_vector2	pos;
}	t_animation_player;

//////////////--ANIMATION--//////////////////////////

t_animation			*new_anim(char *tag, char **frames, int anim_play_time, t_vector2 pos, t_mlx *mlx);
t_frame				*get_frame(t_frame *lst, int frame_nb);
void				draw_frame(t_animation *animation, t_mlx *mlx, int frame);
t_animation			*anim_get_last(t_animation *anim);
t_animation			*get_anim_with_tag(t_animation *anim_list, char *tag);

//////////////--ANIMATION_PLAYER--///////////////////

t_animation_player *new_animation_player(t_animation *animation, t_vector2 pos);
void				hud_char(t_mlx *mlx);
void				switch_anim(t_animation_player *player, char *tag);
t_animation			*hud(t_mlx *mlx);
void				add_animation(t_animation_player *player, t_animation *anim);

//////////////--DEBUG--//////////////////////////////



#endif
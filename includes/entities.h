/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpecquer <jpecquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:43:45 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/17 22:42:23 by jpecquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include "utils.h"
# include "level_editor.h"
# include "animation.h"

typedef struct s_mlx				t_mlx;
typedef struct s_animation_player	t_animation_player;

typedef struct s_entity
{
	t_vector2			pos;
	t_animation_player	*player;
	struct s_entity		*next;
}	t_entity;

t_entity	*new_entity(t_vector2 pos, t_animation_player *player);
void		add_entity(t_entity **lst, t_vector2 pos,
				t_animation_player *player);
#endif
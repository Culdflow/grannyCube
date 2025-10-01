/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:43:45 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/30 17:40:31 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include "utils.h"
# include "level_editor.h"
# include "animation.h"

typedef struct s_mlx t_mlx;
typedef struct s_animation_player t_animation_player;

typedef struct	s_entity
{
	t_vector2			pos;
	t_animation_player	*player;
	struct s_entity		*next;
}	t_entity;


#endif
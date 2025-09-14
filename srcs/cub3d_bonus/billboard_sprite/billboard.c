/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   billboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:16:34 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/14 23:30:31 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	draw_billboard_sprite(int length, int percent, t_billboard *billboard, t_mlx *mlx)
{
	draw_image_scaled(billboard->player->current_anim->frames->current_frame, 1 / length);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_more_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:49:04 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/16 16:49:55 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

void	put_img_to_img(t_img *dst, t_img src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src.size.y)
	{
		j = 0;
		while (j < src.size.x)
		{
			my_mlx_pixel_put(dst, x + j, y + i, get_pixel_img(src, j, i));
			j++;
		}
		i++;
	}
}

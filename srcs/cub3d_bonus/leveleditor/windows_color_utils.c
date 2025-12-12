/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:16:41 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/12 19:17:50 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

char	*rgb_to_str(unsigned int r, unsigned int g, unsigned int b)
{
	char	*result;
	char	*str_r;
	char	*str_g;
	char	*str_b;
	char	*tmp;

	str_r = ft_itoa(r);
	str_g = ft_itoa(g);
	str_b = ft_itoa(b);
	result = ft_strjoin(str_r, ", ");
	tmp = result;
	result = ft_strjoin(result, str_g);
	free(tmp);
	tmp = result;
	result = ft_strjoin(result, ", ");
	free(tmp);
	tmp = result;
	result = ft_strjoin(result, str_b);
	free(tmp);
	free(str_r);
	free(str_g);
	free(str_b);
	return (result);
}

void	draw_sliders(t_mlx *mlx, t_object **sliders)
{
	char			*rgb;

	rgb = rgb_to_str(sliders[0]->value, sliders[1]->value, sliders[2]->value);
	draw_rectangle_no_fill(&mlx->imgs[0], vec2(9, 229), vec2(31, 251),
		0xffffff);
	draw_rectangle(&mlx->imgs[0], vec2(10, 230), vec2(30, 250),
		rgb_to_hex(rgb));
	free(rgb);
	rgb = rgb_to_str(sliders[3]->value, sliders[4]->value, sliders[5]->value);
	draw_rectangle_no_fill(&mlx->imgs[0], vec2(489, 229), vec2(511, 251),
		0xffffff);
	draw_rectangle(&mlx->imgs[0], vec2(490, 230), vec2(510, 250),
		rgb_to_hex(rgb));
	free(rgb);
}

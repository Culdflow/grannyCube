/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:16:41 by dfeve             #+#    #+#             */
/*   Updated: 2026/01/19 20:26:39 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub3d_bonus.h"

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

void	draw_sliders(t_mlx *mlx)
{
	char	*rgb;

	rgb = rgb_to_str(get_object_from_tag(mlx->obj_list, "red_1")->value,
			get_object_from_tag(mlx->obj_list, "green_1")->value,
			get_object_from_tag(mlx->obj_list, "blue_1")->value);
	draw_rectangle_no_fill(&mlx->imgs[0], vec2(499, 99),
		vec2(1001, 501), 0xffffff);
	draw_rectangle(&mlx->imgs[0], vec2(500, 100),
		vec2(1000, 500), rgb_to_hex(rgb));
	free(rgb);
	rgb = rgb_to_str(get_object_from_tag(mlx->obj_list, "red_2")->value,
			get_object_from_tag(mlx->obj_list, "green_2")->value,
			get_object_from_tag(mlx->obj_list, "blue_2")->value);
	draw_rectangle_no_fill(&mlx->imgs[0],
		vec2(499, 599), vec2(1001, 1001), 0xffffff);
	draw_rectangle(&mlx->imgs[0], vec2(500, 600),
		vec2(1000, 1000), rgb_to_hex(rgb));
	free(rgb);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:50:21 by dfeve             #+#    #+#             */
/*   Updated: 2026/01/19 20:38:49 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub3d_bonus.h"

void	on_done_button_click(void *vd_mlx, int idk)
{
	t_mlx	*mlx;

	(void)idk;
	mlx = (t_mlx *)vd_mlx;
	mlx_loop_end(mlx->mlx);
}

t_object	**set_sliders( t_mlx *mlx )
{
	t_object		**sliders;

	sliders = calloc(6, sizeof(t_object *));
	sliders[0] = new_slider(vec2(50, 200), 255, 0xFF0000, mlx);
	sliders[1] = new_slider(vec2(50, 250), 255, 0x00FF00, mlx);
	sliders[2] = new_slider(vec2(50, 300), 255, 0x0000FF, mlx);
	sliders[3] = new_slider(vec2(50, 700), 255, 0xFF0000, mlx);
	sliders[4] = new_slider(vec2(50, 750), 255, 0x00FF00, mlx);
	sliders[5] = new_slider(vec2(50, 800), 255, 0x0000FF, mlx);
	sliders[0]->tag = ft_strdup("red_1");
	sliders[1]->tag = ft_strdup("green_1");
	sliders[2]->tag = ft_strdup("blue_1");
	sliders[3]->tag = ft_strdup("red_2");
	sliders[4]->tag = ft_strdup("green_2");
	sliders[5]->tag = ft_strdup("blue_2");
	add_obj_to_list(&mlx->obj_list, sliders[0]);
	add_obj_to_list(&mlx->obj_list, sliders[1]);
	add_obj_to_list(&mlx->obj_list, sliders[2]);
	add_obj_to_list(&mlx->obj_list, sliders[3]);
	add_obj_to_list(&mlx->obj_list, sliders[4]);
	add_obj_to_list(&mlx->obj_list, sliders[5]);
	return (sliders);
}

char	**set_result(t_object **sliders)
{
	char			**result;

	result = calloc(6, sizeof(char *));
	result[0] = ft_itoa(sliders[0]->value);
	result[1] = ft_itoa(sliders[1]->value);
	result[2] = ft_itoa(sliders[2]->value);
	result[3] = ft_itoa(sliders[3]->value);
	result[4] = ft_itoa(sliders[4]->value);
	result[5] = ft_itoa(sliders[5]->value);
	return (result);
}

void	set_mlx_hook(t_mlx *mlx)
{
	add_obj_to_list(&mlx->obj_list, create_obj(LABEL, vec2(500, 75), 0xFFFFFF,
			"FLOOR COLOR"));
	add_obj_to_list(&mlx->obj_list, create_obj(LABEL, vec2(500, 575), 0xFFFFFF,
			"CEILING COLOR"));
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, fun_exit, mlx->mlx);
	mlx_hook(mlx->win, ON_MOUSEDOWN, 1L << 2, _input_mouse_click_down_ex, mlx);
	mlx_hook(mlx->win, ON_MOUSEUP, 1L << 3, _input_mouse_click_up_ex, mlx);
	mlx_hook(mlx->win, ON_MOUSEMOVE, 1L << 6, _input_mouse, mlx);
}

char	**color_choose_window( void )
{
	t_mlx			*mlx;
	t_object		**sliders;
	t_object		*done_button;
	char			**result;

	mlx = setup_mlx("COLOR CHOOSE", vec2(0, 0));
	result = NULL;
	done_button = obj_set_on_click(create_obj(BUTTON,
				vec2(mlx->screen_size.x - 100, mlx->screen_size.y / 2),
				0xFFFFFF, "DONE"), on_done_button_click, mlx);
	new_image(mlx, mlx->screen_size, vec2(0, 0));
	sliders = set_sliders(mlx);
	draw_sliders(mlx);
	add_obj_to_list(&mlx->obj_list, done_button);
	set_mlx_hook(mlx);
	draw_object_list(mlx, mlx->obj_list);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	mlx_loop(mlx->mlx);
	result = set_result(sliders);
	free(sliders);
	free_mlx(mlx);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:54:41 by dfeve             #+#    #+#             */
/*   Updated: 2025/07/31 01:02:30 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	modif_label_up(void *obj_lst, int new_value)
{
	(void)new_value;
	t_object *newobj_lst;
	newobj_lst = (t_object *)obj_lst;
	newobj_lst->value = newobj_lst->value + 1;
}

void	modif_label_down(void *obj_lst, int new_value)
{
	(void)new_value;
	t_object *newobj_lst;
	newobj_lst = (t_object *)obj_lst;
	newobj_lst->value = newobj_lst->value - 1;
}

void	mlx_loop_end_signal(void *vmlx, int new_value)
{
	(void)new_value;
	t_mlx	*mlx;
	mlx = (t_mlx *)vmlx;
	mlx_loop_end(mlx->mlx);
}

int	fun_exit(t_mlx *mlx)
{
	(void)mlx;
	exit(0);
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:48:46 by dfeve             #+#    #+#             */
/*   Updated: 2025/08/18 18:22:34 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

t_debug_obj	*new_debug_obj(debug_type type, t_vector2 start, t_vector2 end, unsigned int color)
{
	t_debug_obj	*result;

	result = malloc(sizeof(t_debug_obj));
	result->start_pos = start;
	result->end_pos = end;
	result->type = type;
	result->next = NULL;
	result->color = color;
	return (result);
}

t_debug_obj	*debug_obj_get_last(t_debug_obj *lst)
{
	t_debug_obj	*cursor;

	cursor = lst;
	while (cursor && cursor->next)
		cursor = cursor->next;
	return (cursor);
}

void	add_debug_obj(t_debug_obj **lst, t_debug_obj *el)
{
	t_debug_obj	*cursor;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = el;
		return ;
	}
	cursor = debug_obj_get_last(*lst);
	cursor->next = el;
}

void	free_debug_obj(t_debug_obj *lst)
{
	t_debug_obj	*cursor;
	t_debug_obj	*tmp;

	cursor = lst;
	tmp = lst;
	while (cursor)
	{
		tmp = cursor->next;
		free(cursor);
		cursor = tmp;
	}
}

void	draw_debug(t_debug_obj *lst, t_mlx *mlx)
{
	t_debug_obj	*cursor;

	cursor = lst;
	while (cursor)
	{
		if (cursor->type == DOT)
			my_mlx_pixel_put(&mlx->imgs[0], cursor->start_pos.x, cursor->start_pos.y, cursor->color);
		else if (cursor->type == RECTANGLE)
			draw_rectangle(&mlx->imgs[0], cursor->start_pos, cursor->end_pos, cursor->color);
		else if (cursor->type == RECTANGLE_NO_FILL)
			draw_rectangle_no_fill(&mlx->imgs[0], cursor->start_pos, cursor->end_pos, cursor->color);
		else if (cursor->type == LINE)
			draw_line(&mlx->imgs[0], cursor->start_pos, cursor->end_pos, cursor->color);
		cursor = cursor->next;
	}
	free_debug_obj(lst);
}
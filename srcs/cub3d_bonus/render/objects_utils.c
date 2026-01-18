/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:58:13 by dfeve             #+#    #+#             */
/*   Updated: 2026/01/18 01:42:35 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/level_editor.h"

void	board_clicked(t_vector2 mouse_pos, t_vector2 board_size, char **board,
	char turn_to)
{
	t_vector2	screen_size;
	t_vector2	square_size;
	int			x_in_board;
	int			y_in_board;

	screen_size = vec2(1500, 900);
	square_size = vec2(screen_size.x / board_size.x,
			screen_size.y / board_size.y);
	if (mouse_pos.x >= 1520 || mouse_pos.x < 20
		|| mouse_pos.y >= 920 || mouse_pos.y < 20)
		return ;
	x_in_board = (mouse_pos.x - 20) / square_size.x;
	y_in_board = (mouse_pos.y - 20) / square_size.y;
	board[y_in_board][x_in_board] = turn_to;
}

char	get_el_from_board(t_vector2 mouse_pos, t_vector2 board_size,
	char **board)
{
	t_vector2	screen_size;
	t_vector2	square_size;
	int			x_in_board;
	int			y_in_board;

	screen_size = vec2(1500, 900);
	square_size = vec2(screen_size.x / board_size.x,
			screen_size.y / board_size.y);
	if (mouse_pos.x >= 1520 || mouse_pos.x < 20
		|| mouse_pos.y >= 920 || mouse_pos.y < 20)
		return ('\0');
	x_in_board = (mouse_pos.x - 20) / square_size.x;
	y_in_board = (mouse_pos.y - 20) / square_size.y;
	return (board[y_in_board][x_in_board]);
}

void	slider_on_click(void *obj, int u)
{
	t_object	*object;
	t_mlx		*mlx;

	(void)u;
	object = obj;
	mlx = object->victim;
	object->value = (mlx->mouse_pos.x - object->pos.x)
		/ (object->size.x / object->max_value);
	if (object->value > object->max_value)
		object->value = object->max_value;
}

t_object	*new_slider(t_vector2 pos, int max_value, int color, t_mlx *mlx)
{
	t_object	*result;

	result = ft_calloc(1, sizeof(t_object));
	result->pos = pos;
	result->tag = "slider";
	result->size = vec2(265, 40);
	result->value = 0;
	result->max_value = max_value;
	result->type = SLIDER;
	result->color = color;
	result->victim = mlx;
	result->click_func = slider_on_click;
	return (result);
}

t_object	*get_object_from_tag(t_object_list *lst, char *tag)
{
	t_object_list	*cursor;

	cursor = lst;
	while (cursor)
	{
		if (ft_strncmp(cursor->object->tag, tag, ft_strlen(tag)) == 0)
			return (cursor->object);
		cursor = cursor->next;
	}
	return (cursor->object);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:10:15 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/08 16:16:07 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

t_object	*create_obj(int type, void (*onClick)(void *, int), int value, t_vector2 pos, t_vector2 size, int color, char *tag, void *victim)
{
	t_object	*result;
	
	result = malloc(sizeof(t_object));
	result->clickFunc = onClick;
	result->pos = pos;
	result->size = size;
	result->tag  = tag;
	result->type = type;
	result->value = value;
	result->color = color;
	result->victim = victim;
	result->max_value = 0;
	return (result);
}

t_object_list	*get_last_object(t_object_list *start)
{
	if (!start)
		return (NULL);
	while (start->next)
		start = start->next;
	return (start);
}

t_object_list	*new_object_list(t_object *obj)
{
	t_object_list	*result;

	result = malloc(sizeof(t_object_list));
	result->next = NULL;
	result->object = obj;
	return (result);
}

void	add_obj_to_list(t_object_list **lst, t_object *obj)
{
	t_object_list	*last;

	last = get_last_object(*lst);
	if (!last)
	{
		*lst = new_object_list(obj);
		return ;
	}
	last->next = new_object_list(obj);
}

void	free_object_list(t_object_list *start)
{
	t_object_list	*tmp;

	if (!start)
		return ;
	while (start)
	{
		tmp = start->next;
		if (start->object)
			free(start->object);
		free(start);
		start = tmp;
	}
}

void	check_if_obj_clicked(t_vector2 mouse_pos, t_object_list *lst)
{
	while (lst)
	{
		if (check_vector_in_zone(mouse_pos, lst->object->pos, add_vec2(lst->object->pos, lst->object->size)) == TRUE && lst->object->clickFunc)
		{
			if (lst->object->type == SLIDER)
				lst->object->clickFunc(lst->object, lst->object->value);
			else
				lst->object->clickFunc(lst->object->victim, lst->object->value);
			return ;
		}
		lst = lst->next;
	}
}

void	board_clicked(t_vector2 mouse_pos, t_vector2 board_size, char **board, char turn_to)
{
	t_vector2	screen_size;
	t_vector2	square_size;
	int			x_in_board;
	int			y_in_board;

	screen_size = vec2(1500, 900);
	square_size = vec2(screen_size.x / board_size.x, screen_size.y / board_size.y);
	if (mouse_pos.x > 1500 || mouse_pos.x < 20
		|| mouse_pos.y > 900 || mouse_pos.y < 20)
		return ;
	x_in_board = (mouse_pos.x - 20) / square_size.x;
	y_in_board = (mouse_pos.y - 20) / square_size.y;
		board[y_in_board][x_in_board] = turn_to;
}

char	get_el_from_board(t_vector2 mouse_pos, t_vector2 board_size, char **board)
{
		t_vector2	screen_size;
	t_vector2	square_size;
	int			x_in_board;
	int			y_in_board;

	screen_size = vec2(1500, 900);
	square_size = vec2(screen_size.x / board_size.x, screen_size.y / board_size.y);
	if (mouse_pos.x > 1500 || mouse_pos.x < 20
		|| mouse_pos.y > 900 || mouse_pos.y < 20)
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
	object->value = (mlx->mouse_pos.x - object->pos.x) / (object->size.x / object->max_value);
	if (object->value > object->max_value)
		object->value = object->max_value;
}

t_object	*new_slider(t_vector2 pos, int max_value, int color, t_mlx *mlx)
{
	t_object	*result;

	result = ft_calloc(1, sizeof(t_object));
	result->pos = pos;
	result->tag = "slider";
	result->size = vec2(265, 20);
	result->value = 0;
	result->max_value = max_value;
	result->type = SLIDER;
	result->color = color;
	result->victim = mlx;
	result->clickFunc = slider_on_click;
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:10:15 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/28 19:14:13 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

t_object	*obj_set_on_click(t_object *obj, void (*onClick)(void *, int),
	void *victim)
{
	obj->click_func = onClick;
	obj->victim = victim;
	return (obj);
}

t_object	*obj_set_val_size(t_object *obj, int value, t_vector2 size)
{
	obj->value = value;
	obj->size = size;
	return (obj);
}

t_object	*create_obj(int type, t_vector2 pos, int color, char *tag)
{
	t_object	*result;

	result = malloc(sizeof(t_object));
	result->click_func = NULL;
	result->pos = pos;
	result->size = vec2(25, 15);
	result->tag = ft_strdup(tag);
	result->type = type;
	result->value = 0;
	result->color = color;
	result->victim = NULL;
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

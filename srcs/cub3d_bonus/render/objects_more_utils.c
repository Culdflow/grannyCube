/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_more_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:00:15 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/16 18:28:40 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

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
		{
			free(start->object->tag);
			free(start->object);
		}
		free(start);
		start = tmp;
	}
}

void	check_if_obj_clicked(t_vector2 mouse_pos, t_object_list *lst)
{
	while (lst)
	{
		if (check_vector_in_zone(mouse_pos, lst->object->pos,
				add_vec2(lst->object->pos, lst->object->size)) == TRUE
			&& lst->object->clickFunc)
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

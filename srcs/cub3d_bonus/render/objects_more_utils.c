/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_more_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpecquer <jpecquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:00:15 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/18 23:51:40 by jpecquer         ###   ########.fr       */
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
			&& lst->object->click_func)
		{
			if (lst->object->type == SLIDER)
				lst->object->click_func(lst->object, lst->object->value);
			else
				lst->object->click_func(lst->object->victim,
					lst->object->value);
			return ;
		}
		lst = lst->next;
	}
}

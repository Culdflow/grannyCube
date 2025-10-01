/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:05:25 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/24 18:18:46 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/entities.h"

t_entity	*new_entity(t_vector2 pos, t_animation_player *player)
{
	t_entity	*result;

	result = calloc(1, sizeof(t_entity));
	result->next = 0;
	result->player = player;
	result->pos = pos;
	return (result);
}

t_entity	*get_last_entity(t_entity *lst)
{
	t_entity	*cursor;

	cursor = lst;
	while (cursor->next)
		cursor = cursor->next;
	return (cursor);
}

void	add_entity(t_entity *lst, t_vector2 pos, t_animation_player *player)
{
	t_entity	*cursor;

	cursor = get_last_entity(lst);
	cursor->next = new_entity(pos, player);
}

t_entity	*get_entity_from_pos(t_vector2 pos, t_entity *lst)
{
	t_entity	*cursor;
	t_vector2	r_pos;
	t_vector2	r_pos_limit;

	r_pos = mul_vec2(pos, vec2(100, 100));
	r_pos_limit = add_vec2(r_pos, vec2(100, 100));
	cursor = lst;
	while (cursor)
	{
		if ((cursor->pos.x >= r_pos.x && cursor->pos.x <= r_pos_limit.x)
			&& (cursor->pos.y >= r_pos.y && cursor->pos.y <= r_pos_limit.y))
			return (cursor);
		cursor = cursor->next;
	}
	printf("NO ENTITY FOUND CORRESPONDING TO THIS POS (%d, %d)\n", pos.x, pos.y);
	return (NULL);
}
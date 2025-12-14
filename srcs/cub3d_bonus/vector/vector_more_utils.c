/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_more_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:04:49 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/14 15:07:40 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

t_vector2	vec2_inv_y(t_vector2 vec)
{
	t_vector2	result;

	result.y = vec.y * -1;
	result.x = vec.x;
	return (result);
}

t_vector2	vec2_inv(t_vector2 vec)
{
	t_vector2	result;

	result.y = vec.y * -1;
	result.x = vec.x * -1;
	return (result);
}

int	reverse_bool(int a)
{
	if (a == 0 || a == -1)
		return (1);
	else
		return (0);
}

int	check_vector_in_zone(t_vector2 mouse_pos, t_vector2 zone_start,
		t_vector2 zone_end)
{
	zone_start = vec2_make_start(zone_start, zone_end);
	zone_end = vec2_make_end(zone_start, zone_end);
	if (mouse_pos.x >= zone_start.x && mouse_pos.x <= zone_end.x
		&& mouse_pos.y >= zone_start.y && mouse_pos.y <= zone_end.y)
		return (TRUE);
	return (FALSE);
}

t_vector2	convert_floatvec(t_vector2_float vecf)
{
	t_vector2	vec;

	vec = vec2((int)vecf.x, (int)vecf.y);
	return (vec);
}

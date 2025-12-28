/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:19:52 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/28 19:14:13 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

int	clamp(int *nb, int min, int max)
{
	if (min > max)
		return (0);
	if (*nb < min)
	{
		*nb = min;
		return (-1);
	}
	else if (*nb > max)
	{
		*nb = max;
		return (-1);
	}
	return (0);
}

t_vector2	mul_vec2(t_vector2 vec1, t_vector2 vec2)//Returns vec1 * vec2
{
	t_vector2	result;

	result.x = vec1.x * vec2.x;
	result.y = vec1.y * vec2.y;
	return (result);
}

int	clamp_vec2(t_vector2 *vec, t_vector2 min, t_vector2 max)
{
	int	is_invalid;

	is_invalid = 0;
	if (clamp(&vec->x, min.x, max.x) < 0)
		is_invalid = -1;
	if (clamp(&vec->y, min.y, max.y) < 0)
		is_invalid = -1;
	if (is_invalid < 0)
		return (-1);
	return (0);
}

int	compare_vec2(t_vector2 vec1, t_vector2 vec2)
{
	return (vec1.x == vec2.x && vec1.y == vec2.y);
}

t_vector2	vec2_inv_x(t_vector2 vec)
{
	t_vector2	result;

	result.y = vec.y;
	result.x = vec.x * -1;
	return (result);
}

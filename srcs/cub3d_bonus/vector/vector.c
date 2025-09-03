/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:19:13 by dfeve             #+#    #+#             */
/*   Updated: 2025/07/23 18:09:21 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

t_vector2	vec2(int x, int y)//Returns vector2 with values x and y
{
	t_vector2	result;

	result.x = x;
	result.y = y;
	return (result);
}

t_vector2	vec2_make_start(t_vector2 start, t_vector2 end)
{
	t_vector2	result;

	result.x = start.x;
	if (start.x > end.x)
		result.x = end.x;
	result.y = start.y;
	if (start.y > end.y)
		result.y = end.y;
	return (result);
}

t_vector2	vec2_make_end(t_vector2 start, t_vector2 end)//Reverse vec2_make_start
{
	t_vector2	result;

	result.x = end.x;
	if (start.x > end.x)
		result.x = start.x;
	result.y = end.y;
	if (start.y > end.y)
		result.y = start.y;
	return (result);
}

t_vector2	add_vec2(t_vector2 vec1, t_vector2 vec2)//returns vec1 + vec2
{
	t_vector2	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	return (result);
}

t_vector2	sub_vec2(t_vector2 vec1, t_vector2 vec2)//Returns vec1 - vec2
{
	t_vector2		result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	return (result);
}

t_vector2	div_vec2(t_vector2 vec1, t_vector2 divi)
{
	t_vector2	result;

	result = vec2(0, 0);
	if (divi.x > 0)
		result.x = vec1.x / divi.x;
	if (divi.y > 0)
	result.y = vec1.y / divi.y;
	return (result);
}

int	abs(int x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

void	free_tab(char **tab, t_vector2 tab_size)
{
	int cursor;

	cursor = 0;
	if (!tab)
		return ;
	while (cursor < tab_size.y)
	{
		if (tab[cursor])
			free(tab[cursor]);
		cursor++;
	}
	free(tab);
}

void	ft_approach(int *a, int app)
{
	if (*a < app)
		(*a)++;
	else
		(*a)--;
}
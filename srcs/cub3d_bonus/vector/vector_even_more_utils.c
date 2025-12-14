/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_even_more_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:07:57 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/14 15:12:52 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

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
	int	cursor;

	cursor = 0;
	if (!tab)
		return ;
	while (cursor < tab_size.y)
	{
		if (tab[cursor])
		{
			printf("freeing line: %s\n", tab[cursor]);
			free(tab[cursor]);
		}
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

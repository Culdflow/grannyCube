/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:42:13 by mabdessm          #+#    #+#             */
/*   Updated: 2025/12/14 15:10:06 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	replace_the_spaces(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					map[i][j] = ' ';
			}
			++j;
		}
		++i;
	}
}

void	replace_the_spaces_backwards(char **map)
{
	int	i;
	int	j;

	i = ft_strstrlen(map) - 1;
	while (map && i >= 0)
	{
		j = ft_strlen(map[i]) - 1;
		while (j >= 0)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					map[i][j] = ' ';
			}
			--j;
		}
		--i;
	}
}

char	**close_map(char **map)
{
	char	**new_map;

	new_map = ft_calloc(sizeof(char *), ft_strstrlen(map) + 3);
	fill_map(new_map, map);
	replace_the_spaces(new_map);
	replace_the_spaces_backwards(new_map);
	return (new_map);
}

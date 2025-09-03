/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:42:13 by mabdessm          #+#    #+#             */
/*   Updated: 2025/06/03 16:54:01 by mabdessm         ###   ########.fr       */
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

	printf("og map\n"); //test
	draw_map(map); //test
	new_map = ft_calloc(sizeof(char *), ft_strstrlen(map) + 3);
	fill_map(new_map, map);
	printf("new map with the surrounding spaces without the replacement\n"); //test
	draw_map(new_map); //test
	replace_the_spaces(new_map);
	replace_the_spaces_backwards(new_map);
	printf("final map\n"); //test
	draw_map(new_map); //test
	return (new_map);
}

/*int	main() //test avec une map faite au brut force
{
	char	**map;

	map = ft_calloc(sizeof(char *), 7);
	map[0] = ft_calloc(sizeof(char), 5);
	map[1] = ft_calloc(sizeof(char), 5);
	map[2] = ft_calloc(sizeof(char), 5);
	map[3] = ft_calloc(sizeof(char), 5);
	map[4] = ft_calloc(sizeof(char), 5);
	map[5] = ft_calloc(sizeof(char), 5);
	map[0][0] = '0';
	map[0][1] = '1';
	map[0][2] = '0';
	map[0][3] = '0';
	map[1][0] = '1';
	map[1][1] = '1';
	map[1][2] = '1';
	map[1][3] = '0';
	map[2][0] = '0';
	map[2][1] = '1';
	map[2][2] = '0';
	map[2][3] = '1';
	map[3][0] = '1';
	map[3][1] = '0';
	map[3][2] = '0';
	map[3][3] = '1';
	map[4][0] = '0';
	map[4][1] = '1';
	map[4][2] = '1';
	map[4][3] = '1';
	map[5][0] = '0';
	map[5][1] = '1';
	map[5][2] = '0';
	map[5][3] = '1';
	close_map(map);
}*/

//a faire

//mettre tous ca (ma partie et celle de dim) dans la partie bonus
//comme ca on accede aux fonctions de mon parsing et lier les deux,
//quand la map est generé elle passe par le parsing pour verifier si
//elle est bonne sinon error
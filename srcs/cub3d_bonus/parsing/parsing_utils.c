/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:29:39 by mabdessm          #+#    #+#             */
/*   Updated: 2025/06/03 16:01:35 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	map_not_closed(char **map)
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
					return (1);
			}
			++j;
		}
		++i;
	}
	return (0);
}

void	fill_map(char **new_map, char **map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < (unsigned int)(ft_strstrlen(map) + 2))
	{
		new_map[i] = ft_calloc(sizeof(char), longest_line(map) + 3);
		j = 0;
		while (j < longest_line(map) + 2)
		{
			if (i == 0 || i == (unsigned int)ft_strstrlen(map) + 1 || j == 0
				|| j == longest_line(map) + 1)
				new_map[i][j] = ' ';
			else if (map[i - 1] && j - 1 < ft_strlen(map[i - 1]))
				new_map[i][j] = map[i - 1][j - 1];
			else
				new_map[i][j] = ' ';
			++j;
		}
		++i;
	}
}

int	no_map_errors(char **map, t_data *data)
{
	unsigned int	i;
	unsigned int	j;
	char			**new_map;

	i = -1;
	while (map && map[++i])
	{
		j = -1;
		while (map[i] && map[i][++j])
		{
			if (invalid_character(map[i][j]))
				return (return_error("Invalid characters in map!"));
			if (duplicate_player(map[i][j], data))
				return (return_error("Muliple Players in map!"));
		}
	}
	new_map = ft_calloc(sizeof(char *), ft_strstrlen(map) + 3);
	fill_map(new_map, map);
	if (map_not_closed(new_map))
	{
		ft_free_tab(new_map);
		return (return_error("Map is not closed/surrouned by walls!"));
	}
	ft_free_tab(new_map);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	signe;
	int	x;

	i = 0;
	x = 0;
	signe = 1;
	while (((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		&& nptr[i] != '\0')
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signe = signe * -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9') && nptr[i] != '\0')
	{
		x = x * 10 + (nptr[i] - '0');
		i++;
	}
	return (x * signe);
}

char	*extract_texture_path(char *file, int *i, int *counter, char **dest)
{
	char	*temp;
	int		j;

	j = 0;
	++(*counter);
	if (*counter > 1)
		return (NULL);
	*i += 3;
	while (file[*i] == ' ')
		++(*i);
	temp = ft_calloc(sizeof(char *), ft_strlen(file) + 1);
	while (file[*i] != '\n' && file[*i] != ' ')
		temp[j++] = file[(*i)++];
	while (file[*i] == ' ')
		++(*i);
	if (file[*i] != '\n')
		return (NULL);
	*dest = ft_strdup(temp);
	free(temp);
	return (*dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:29:42 by mabdessm          #+#    #+#             */
/*   Updated: 2025/07/19 23:23:39 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	check_floor_color(t_data *data, char *str)
{
	int	i;

	data->seperated_floor_color = ft_split(str, ',');
	if (ft_strstrlen(data->seperated_floor_color) != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (color_valid_to_atoi(data->seperated_floor_color[i]))
		{
			if (ft_atoi(data->seperated_floor_color[i]) < 0
				|| ft_atoi(data->seperated_floor_color[i]) > 255)
				return (0);
		}
		else
			return (0);
		++i;
	}
	return (1);
}

int	valid_color(t_data *data, char *str, int x)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != ',' && !(ft_isdigit(str[i])))
			return (0);
		if (str[i] == ',')
			++j;
		++i;
	}
	if (j != 2)
		return (0);
	if (x)
		return (check_floor_color(data, str));
	else
		return (check_ceiling_color(data, str));
}

int	valid_colors(t_data *data)
{
	if (!(valid_color(data, data->floor_color, 1)))
	{
		data->invalid_floor_color = 1;
		return (0);
	}
	else if (!(valid_color(data, data->ceiling_color, 0)))
		return (0);
	else
		return (1);
}

char	**check_errors(char *file, t_data *data)
{
	int		fd;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0 || invalid_file(file))
		return (file_errors(fd, file));
	map = check_file_errors(fd, data);
	if (!map)
		return (NULL);
	else
	{
		if (valid_colors(data))
			return (map);
		else
		{
			ft_free_tab(map);
			if (data->invalid_floor_color)
				return_error("Invalid floor color!");
			else
				return_error("Invalid ceiling color!");
			return (NULL);
		}
	}
}

void	refill_map(char ***map_ptr)
{
	char			**map;
	char			**new_map;
	unsigned int	i;
	unsigned int	j;

	map = *map_ptr;
	new_map = malloc(sizeof(char *) * (ft_strstrlen(map) + 2 + 1));
	if (!new_map)
		return ;
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
	new_map[i] = NULL;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	*map_ptr = new_map;
}

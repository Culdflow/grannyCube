/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:35:41 by mabdessm          #+#    #+#             */
/*   Updated: 2025/06/03 16:01:29 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

char	*get_map(char *file, t_data *data)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	if (!parse_elements(file, data, &i))
		return (NULL);
	while (file[i] == '\n')
		++i;
	temp = ft_calloc(sizeof(char *), (ft_strlen(file) - i) + 1);
	j = 0;
	while (file[i])
		temp[j++] = file[i++];
	return (temp);
}

char	**return_null_error(void)
{
	return_error("File is empty!");
	return (NULL);
}

char	**return_check_file_errors(char	**map, t_data *data)
{
	if (no_map_errors(map, data))
		return (map);
	ft_free_tab(map);
	return (NULL);
}

char	**check_file_errors(int fd, t_data *data)
{
	char	**map;
	char	*temp;
	char	*buffer;
	char	*old_buffer;

	buffer = get_next_line(fd);
	if (!buffer)
		return (return_null_error());
	temp = get_next_line(fd);
	while (temp)
	{
		old_buffer = buffer;
		buffer = ft_strjoin(buffer, temp);
		double_free(old_buffer, temp);
		temp = get_next_line(fd);
	}
	close(fd);
	old_buffer = get_map(buffer, data);
	free(buffer);
	buffer = old_buffer;
	if (!buffer || empty_lines_in_map(buffer))
		return (buffer_errors(buffer, data));
	map = ft_split(buffer, '\n');
	free(buffer);
	return (return_check_file_errors(map, data));
}

int	check_ceiling_color(t_data *data, char *str)
{
	int	i;

	data->seperated_ceiling_color = ft_split(str, ',');
	if (ft_strstrlen(data->seperated_ceiling_color) != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (color_valid_to_atoi(data->seperated_ceiling_color[i]))
		{
			if (ft_atoi(data->seperated_ceiling_color[i]) < 0
				|| ft_atoi(data->seperated_ceiling_color[i]) > 255)
				return (0);
		}
		else
			return (0);
		++i;
	}
	return (1);
}

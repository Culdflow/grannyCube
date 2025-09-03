/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:30:34 by mabdessm          #+#    #+#             */
/*   Updated: 2025/06/03 16:01:33 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

char	*extract_color(char *file, int *i, int *counter, char **destination)
{
	char	*temp;
	int		j;

	j = 0;
	++(*counter);
	if (*counter > 1)
		return (NULL);
	*i += 2;
	while (file[*i] == ' ')
		++(*i);
	temp = ft_calloc(sizeof(char *), ft_strlen(file) + 1);
	while (file[*i] != '\n')
		temp[j++] = file[(*i)++];
	*destination = ft_strdup(temp);
	free(temp);
	return (*destination);
}

int	invalid_element1(t_data *data, char *file, int *i, char c)
{
	if (c == 'N')
	{
		if (file[*i] == 'N' && file[*i + 1] == 'O' && file[*i + 2] == ' ')
			if (!extract_texture_path(file, i, &data->number_of_no,
					&data->path_to_the_north_texture))
				return (1);
	}
	else if (c == 'S')
	{
		if (file[*i] == 'S' && file[*i + 1] == 'O' && file[*i + 2] == ' ')
			if (!extract_texture_path(file, i, &data->number_of_so,
					&data->path_to_the_south_texture))
				return (1);
	}
	else if (c == 'W')
	{
		if (file[*i] == 'W' && file[*i + 1] == 'E' && file[*i + 2] == ' ')
			if (!extract_texture_path(file, i, &data->number_of_we,
					&data->path_to_the_west_texture))
				return (1);
	}
	return (0);
}

int	invalid_element2(t_data *data, char *file, int *i, char c)
{
	if (c == 'E')
	{
		if (file[*i] == 'E' && file[*i + 1] == 'A' && file[*i + 2] == ' ')
			if (!extract_texture_path(file, i, &data->number_of_ea,
					&data->path_to_the_east_texture))
				return (1);
	}
	else if (c == 'F')
	{
		if (file[*i] == 'F' && file[*i + 1] == ' ')
			if (!extract_color(file, i, &data->number_of_f, &data->floor_color))
				return (1);
	}
	else if (c == 'C')
	{
		if (file[*i] == 'C' && file[*i + 1] == ' ')
			if (!extract_color(file, i, &data->number_of_c,
					&data->ceiling_color))
				return (1);
	}
	return (0);
}

int	is_valid_element(char *file, int *i)
{
	if ((file[*i] == 'N' && file[*i + 1] == 'O' && file[*i + 2] == ' ')
		|| (file[*i] == 'S' && file[*i + 1] == 'O' && file[*i + 2] == ' ')
		|| (file[*i] == 'W' && file[*i + 1] == 'E' && file[*i + 2] == ' ')
		|| (file[*i] == 'E' && file[*i + 1] == 'A' && file[*i + 2] == ' ')
		|| (file[*i] == 'F' && file[*i + 1] == ' ')
		|| (file[*i] == 'C' && file[*i + 1] == ' '))
		return (1);
	return (0);
}

char	*parse_elements(char *file, t_data *data, int *i)
{
	int	count;

	count = -1;
	while (++count < 6)
	{
		while (file[*i] == '\n' || file[*i] == ' ')
			++(*i);
		if (!is_valid_element(file, i))
			return (NULL);
		else if (invalid_element1(data, file, i, 'N')
			|| invalid_element1(data, file, i, 'S')
			|| invalid_element1(data, file, i, 'W')
			|| invalid_element2(data, file, i, 'E')
			|| invalid_element2(data, file, i, 'F')
			|| invalid_element2(data, file, i, 'C'))
			return (NULL);
	}
	if (data->number_of_no && data->number_of_so && data->number_of_we
		&& data->number_of_ea && data->number_of_f && data->number_of_c)
		return (file);
	else
		return (NULL);
}

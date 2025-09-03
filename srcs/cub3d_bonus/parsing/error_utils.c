/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:31:22 by mabdessm          #+#    #+#             */
/*   Updated: 2025/06/03 16:01:26 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	no_element(t_data *data)
{
	if (data->number_of_no == 0 || data->number_of_so == 0
		|| data->number_of_we == 0 || data->number_of_ea == 0
		|| data->number_of_f == 0 || data->number_of_c == 0)
		return (1);
	return (0);
}

char	**buffer_errors(char *buffer, t_data *data)
{
	if (!buffer)
	{
		if (data->number_of_no > 1)
			return_error("Map has multiple NO elements!");
		else if (data->number_of_so > 1)
			return_error("Map has Multiple SO elements!");
		else if (data->number_of_we > 1)
			return_error("Map has multiple WE elements!");
		else if (data->number_of_ea > 1)
			return_error("Map has multiple EA elements!");
		else if (data->number_of_f > 1)
			return_error("Map has multiple F elements!");
		else if (data->number_of_c > 1)
			return_error("Map has multiple C elements!");
		else if (no_element(data))
			more_error_messages(data);
		else
			return_error("Map is Invalid!");
	}
	else if (empty_lines_in_map(buffer))
	{
		free(buffer);
		return_error("Map contains an empty line!");
	}
	return (NULL);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		++i;
	return (i);
}

int	color_valid_to_atoi(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ')
		++i;
	if (!(ft_isdigit(str[i])))
		return (0);
	while (ft_isdigit(str[i]))
		++i;
	while (str[i] == ' ')
		++i;
	if (str[i])
		return (0);
	return (1);
}

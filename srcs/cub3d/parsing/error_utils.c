/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpecquer <jpecquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:31:22 by mabdessm          #+#    #+#             */
/*   Updated: 2026/01/12 15:16:07 by jpecquer         ###   ########.fr       */
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

static void	error_empty(char *buffer)
{
	free(buffer);
	return_error("Map contains an empty line!");
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
		else if (data->number_of_g > 1)
			return_error("Map has multiple G elements!");
		else if (no_element(data))
			more_error_messages(data);
		else
			return_error("Map is Invalid!");
	}
	else if (empty_lines_in_map(buffer))
		error_empty(buffer);
	return (NULL);
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

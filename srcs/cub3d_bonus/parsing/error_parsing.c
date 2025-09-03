/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:31:35 by mabdessm          #+#    #+#             */
/*   Updated: 2025/06/03 16:01:23 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	return_error(char *str)
{
	printf("\033[0;31mError\n");
	printf("%s\n\033[0m", str);
	return (0);
}

int	invalid_file(char *str)
{
	unsigned int	i;

	i = ft_strlen(str) - 1;
	if (!str[i] || str[i] != 'b')
		return (1);
	--i;
	if (!str[i] || str[i] != 'u')
		return (1);
	--i;
	if (!str[i] || str[i] != 'c')
		return (1);
	--i;
	if (!str[i] || str[i] != '.')
		return (1);
	--i;
	if (!str[i])
		return (1);
	return (0);
}

char	**file_errors(int fd, char *file)
{
	if (fd < 0)
		return_error("Argument doesn't exist or is not a file!");
	else if (invalid_file(file))
		return_error("Invalid file type!");
	return (NULL);
}

int	empty_lines_in_map(char *buffer)
{
	int	i;

	i = 0;
	if (buffer[i] == '\n')
		return (1);
	while (buffer[i] && buffer[i + 1])
	{
		if (buffer[i] == '\n' && buffer[i + 1] == '\n')
			return (1);
		++i;
	}
	return (0);
}

void	more_error_messages(t_data *data)
{
	if (data->number_of_no == 0)
		return_error("Map has no NO element or an invalid element before it!");
	else if (data->number_of_so == 0)
		return_error("Map has no SO element or an invalid element before it!");
	else if (data->number_of_we == 0)
		return_error("Map has no WE element or an invalid element before it!");
	else if (data->number_of_ea == 0)
		return_error("Map has no EA element or an invalid element before it!");
	else if (data->number_of_f == 0)
		return_error("Map has no F element or an invalid element before it!");
	else if (data->number_of_c == 0)
		return_error("Map has no C element or an invalid element before it!");
}

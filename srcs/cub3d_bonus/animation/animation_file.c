/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:58:38 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/24 18:01:00 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/animation.h"

int	get_file_length(char *file)
{
	int		fd;
	int		start;
	int		result;
	char	*buffer;

	start = TRUE;
	result = 0;
	buffer = NULL;
	fd = open(file, O_RDONLY);
	while (buffer || start)
	{
		start = FALSE;
		if (buffer)
			free(buffer);
		buffer = get_next_line(fd);
		result++;
	}
	close(fd);
	return (result);
}

char	**file_load_frames(char *file)
{
	char	**result;
	int		fd;
	int		i;
	char	*buffer;

	printf("loading file: %s\n", file);
	result = ft_calloc(get_file_length(file) + 1, sizeof(char *));
	fd = open(file, O_RDONLY);
	i = 0;
	buffer = NULL;
	fd = open(file, O_RDONLY);
	while (buffer || i == 0)
	{
		if (buffer)
			free(buffer);
		buffer = get_next_line(fd);
		result[i++] = ft_strtrim(buffer, "\n");
	}
	result[i] = 0;
	close(fd);
	return (result);
}
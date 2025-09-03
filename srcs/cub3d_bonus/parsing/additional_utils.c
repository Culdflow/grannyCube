/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:33:44 by mabdessm          #+#    #+#             */
/*   Updated: 2025/07/30 00:16:39 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	double_free(char *str1, char *str2)
{
	free (str1);
	free (str2);
}

void	ft_free_tab(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free (str[i]);
	free (str);
}

int	invalid_character(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != '\n'
		&& c != 'W' && c != ' ')
		return (1);
	return (0);
}

int	duplicate_player(char c, t_data *data)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		++data->number_of_players;
	if (data->number_of_players > 1)
		return (1);
	return (0);
}

unsigned int	longest_line(char **map)
{
	int				i;
	unsigned int	result;

	i = 0;
	result = 0;
	while (map && map[i])
	{
		if (ft_strlen(map[i]) > result)
			result = ft_strlen(map[i]);
		++i;
	}
	return (result);
}

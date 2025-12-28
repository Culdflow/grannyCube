/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_again.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:29:23 by jpecquer          #+#    #+#             */
/*   Updated: 2025/12/28 18:43:32 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/bonus/cub3d_bonus.h"

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

void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx->win, ON_KEYDOWN, (1L << 0), on_keypress, data);
	mlx_hook(data->mlx->win, ON_KEYUP, (1L << 1), on_keyrelease, data);
	mlx_hook(data->mlx->win, ON_DESTROY, 0, free_data, data);
	mlx_loop_hook(data->mlx->mlx, draw_textures, data);
	mlx_loop(data->mlx->mlx);
	free_data(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:11:23 by dfeve             #+#    #+#             */
/*   Updated: 2025/07/30 00:06:22 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

t_img	*create_img(char *path, t_mlx *mlx)
{
	void	*temp;
	t_img	*img;

	img = malloc(sizeof(t_img));
	temp = mlx_xpm_file_to_image(mlx->mlx, path, &img->size.x, &img->size.y);
	if (temp == NULL)
	{
		printf("img not valid\n");
		free(img);
		return (NULL);
	}
	mlx_destroy_image(mlx->mlx, temp);
	img->img = mlx_xpm_file_to_image(mlx->mlx, path, &img->size.x, &img->size.y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	return (img);
}

t_textures	*new_textures(unsigned int floor_color, unsigned int ceiling_color, t_data *data)
{
	t_textures	*result;

	result = malloc(sizeof(t_textures));
	result->floor_color = floor_color;
	result->ceiling_color = ceiling_color;
	result->north_texture = create_img(data->path_to_the_north_texture, data->mlx);
	result->south_texture = create_img(data->path_to_the_south_texture, data->mlx);
	result->east_texture = create_img(data->path_to_the_east_texture, data->mlx);
	result->west_texture = create_img(data->path_to_the_west_texture, data->mlx);
	result->fog_texture = create_img(FOG_TEXT, data->mlx);
	return (result);
}

void	free_textures(t_textures **textures, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, (*textures)->north_texture->img);
	mlx_destroy_image(mlx->mlx, (*textures)->south_texture->img);
	mlx_destroy_image(mlx->mlx, (*textures)->east_texture->img);
	mlx_destroy_image(mlx->mlx, (*textures)->west_texture->img);
	free((*textures)->north_texture);
	free((*textures)->south_texture);
	free((*textures)->east_texture);
	free((*textures)->west_texture);
	free((*textures));
}

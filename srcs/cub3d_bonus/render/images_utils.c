/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:17:25 by dfeve             #+#    #+#             */
/*   Updated: 2025/08/29 19:39:50 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/level_editor.h"

int	count_images(t_mlx *mlx)
{
	int	count;

	count = 0;
	while (mlx->imgs[count].img)
		count++;
	return (count);
}

void	add_image(t_mlx *mlx, t_img img)
{
	int	nb_images;

	if (!img.img)
		printf("WTFFFFF\n");
	nb_images = count_images(mlx);
	mlx->imgs[nb_images] = img;
	mlx->imgs[nb_images + 1].img = NULL;
	nb_images = count_images(mlx);
}

void	del_images(t_mlx *mlx)
{
	int	nb_imgs;

	nb_imgs = count_images(mlx) - 1;
	if (nb_imgs == -1)
		return ;
	mlx_destroy_image(mlx->mlx, mlx->imgs[0].img);
	mlx->imgs[0].img = NULL;
}

void	draw_image_scaled(t_img *img, float scale, t_vector2 pos, t_mlx *mlx)
{
	t_vector2	cursor;
	float		img_cursor_x;
	float		img_cursor_y;

	cursor = pos;
	img_cursor_x = 0;
	img_cursor_y = 0;
	while (img_cursor_y < img->size.y)
	{
		img_cursor_x = 0;
		cursor.x = pos.x;
		while (img_cursor_x < img->size.x)
		{
			if (cursor.x >= 0 && cursor.x < mlx->screen_size.x && cursor.y >= 0 && cursor.y < mlx->screen_size.y)
				my_mlx_pixel_put(&mlx->imgs[0], cursor.x, cursor.y, get_pixel_img(*img, img_cursor_x, img_cursor_y));
			img_cursor_x += 1 / scale;
			cursor.x++;
		}
		img_cursor_y += 1 / scale;
		cursor.y++;
	}
}

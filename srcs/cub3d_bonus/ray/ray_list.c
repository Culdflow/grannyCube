/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 03:05:49 by dfeve             #+#    #+#             */
/*   Updated: 2025/08/25 16:43:30 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

t_ray_list	*new_ray_list(int fov, int base_angle, t_vector2 start_pos, t_mlx *mlx)
{
	t_ray_list	*result;
	t_ray		*cursor;
	float		angle;

	result = malloc(sizeof(t_ray_list));
	angle = base_angle - (fov / 2);
	if (angle < 0)
		angle = 360 - ft_fabsf(angle);
	angle = ft_fmodulf(angle, 360);
	result->ray_list = new_ray(start_pos, angle, mlx);
	result->fov = fov;
	angle += 0.5;
	cursor = result->ray_list;
	while ((int)angle != (base_angle + (fov / 2)) % 360)
	{
		if (angle < 0)
			angle = 360 - ft_fabsf(angle);
		angle = ft_fmodulf(angle, 360);
		// printf("angle = %d\n", angle);
		cursor->next_ray = new_ray(start_pos, angle, mlx);
		cursor = cursor->next_ray;
		angle += (((float)(fov) / (float)mlx->screen_size.x) * 4);
	}
	return (result);
}

void	draw_ray_list(t_ray_list *ray_list, t_vector2 start_pos, t_mlx *mlx)
{
	t_ray	*ray;

	ray = ray_list->ray_list;
	while (ray)
	{
		draw_ray(start_pos, ray, mlx);
		ray = ray->next_ray;
	}
}

void	free_ray_list(t_ray_list **ray_list)
{
	t_ray	*cursor;
	t_ray	*tmp;

	// printf("freeing ray list\n");
	if (!(*ray_list) || !ray_list)
		return ;
	cursor = (*ray_list)->ray_list;
	while (cursor)
	{
		tmp = cursor->next_ray;
		free(cursor);
		cursor = tmp;
	}
	free(*ray_list);
}
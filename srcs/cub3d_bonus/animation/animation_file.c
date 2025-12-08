/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:58:38 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/08 02:16:51 by dfeve            ###   ########.fr       */
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

void	draw_frame(t_animation *animation, t_mlx *mlx, int frame)
{
	t_frame	*frame_temp;

	add_image(mlx, *animation->frames->current_frame->frame);
	frame_temp = get_frame(animation->frames,
			animation->frames->current_frame->frame_nb + 1);
	if (frame == animation->next_frame || animation->next_frame == -1)
	{
		animation->next_frame = (frame + (30 / animation->anim_play_time)) % 30;
		if (frame_temp)
			animation->frames->current_frame = frame_temp;
		else if (animation->loop)
			animation->frames->current_frame = animation->frames;
	}
}

void	free_frame_struct(t_frame *frame, t_mlx *mlx)
{
	t_frame	*cursor;
	t_frame	*tmp;

	(void)mlx;
	cursor = frame;
	tmp = frame;
	while (cursor)
	{
		tmp = cursor->next;
		if (cursor->frame->img)
			printf("IMAGES IS ALIVE\n");
		else
			printf("I AM NOT ALIVE\n");
		mlx_destroy_image(mlx->mlx, cursor->frame->img);
		free(cursor->frame->img);
		free(cursor->frame);
		free(cursor);
		cursor = tmp;
	}
}

void	free_animation_struct(t_animation *anim_list, t_mlx *mlx)
{
	t_animation	*cursor;
	t_animation	*tmp;

	cursor = anim_list;
	tmp = anim_list;
	while (cursor)
	{
		tmp = cursor->next;
		free_frame_struct(cursor->frames, mlx);
		free(cursor);
		cursor = tmp;
	}
}

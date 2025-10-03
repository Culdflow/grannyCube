/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:54:51 by dfeve             #+#    #+#             */
/*   Updated: 2025/10/03 02:13:16 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/animation.h"

t_frame	*load_frames(char **frames, t_vector2 pos, t_mlx *mlx)
{
	t_frame *result;
	t_frame	*cursor;
	int		i;

	i = 0;
	result = ft_calloc(1, sizeof(t_frame));
	cursor = result;
	while (frames && frames[i])
	{
		cursor->frame_nb = i;
		cursor->frame = xpm_file_to_img(mlx, frames[i], pos);
		cursor->current_frame = 0;
		i++;
		if (frames[i])
		{
			cursor->next = ft_calloc(1, sizeof(t_frame));
			cursor = cursor->next;
		}
		else
			cursor->next = 0;
	}
	return (result);
}

t_frame	*get_frame(t_frame *lst, int frame_nb)
{
	t_frame *cursor;

	cursor = lst;
	while (cursor && cursor->frame_nb != frame_nb)
		cursor = cursor->next;
	return (cursor);
}

t_animation	*new_anim(char *tag, char **frames, int anim_play_time, t_vector2 pos, t_mlx *mlx)
{
	t_animation	*result;

	result = malloc(sizeof(t_animation));
	result->frames = load_frames(frames, pos, mlx);
	result->frames->current_frame = result->frames;
	result->anim_tag = tag;
	result->anim_play_time = anim_play_time;
	result->loop = FALSE;
	result->next_frame = -1;
	result->next = 0;
	return (result);
}

t_animation	*anim_get_last(t_animation *anim_list)
{
	t_animation *cursor;

	cursor = anim_list;
	while (cursor && cursor->next)
		cursor = cursor->next;
	return (cursor);
}

t_animation	*get_anim_with_tag(t_animation *anim_list, char *tag)
{
	t_animation	*cursor;

	cursor = anim_list;
	while (cursor)
	{
		printf("looking at tag %s\n", cursor->anim_tag);
		if (ft_strncmp(tag, cursor->anim_tag, ft_strlen(tag)) == 0)
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}

void	draw_frame(t_animation *animation, t_mlx *mlx, int frame)
{
	t_frame	*frame_temp;

	add_image(mlx, *animation->frames->current_frame->frame);
	frame_temp = get_frame(animation->frames, animation->frames->current_frame->frame_nb + 1);
	if (frame == animation->next_frame || animation->next_frame == -1)
	{
		animation->next_frame = (frame + (30 / animation->anim_play_time)) % 30;
		if (frame_temp)
				animation->frames->current_frame = frame_temp;
		else if (animation->loop)
			animation->frames->current_frame = animation->frames;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:30:05 by dfeve             #+#    #+#             */
/*   Updated: 2025/08/28 18:26:57 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/animation.h"

t_animation_player *new_animation_player(t_animation *animation, t_vector2 pos)
{
	t_animation_player	*result;

	result = calloc(1, sizeof(t_animation_player));
	result->anim_list = animation;
	result->current_anim = animation;
	result->pos = pos;
	return (result);
}

void	add_animation(t_animation_player *player, t_animation *anim)
{
	t_animation *last_anim;
	
	last_anim = anim_get_last(player->anim_list);
	last_anim->next = anim;
}

void	switch_anim(t_animation_player *player, char *tag)
{
	t_animation *anim;

	if	(ft_strncmp(tag, player->current_anim->anim_tag, ft_strlen(tag)) == 0)
		return ;
	printf("looking for tag %s\n", tag);
	anim = get_anim_with_tag(player->anim_list, tag);
	if (anim)
		player->current_anim = anim;
}

t_animation	*hud(t_mlx *mlx)
{
	t_animation	*result;

	char *test[] = {"textures/HUD/HUD.xpm", 0};
	result = new_anim("HUD_TEST", test, 4, vec2(0, 0), mlx);
	result->loop = TRUE;
	return (result);
}
void	hud_char(t_mlx *mlx)
{
	t_animation	*result;
	t_animation	*result_state_2;
	t_animation	*result_state_3;

	char	*anim[] = {"textures/HUD/HUD_char_state1_neutral.xpm", "textures/HUD/HUD_char_state1_neutral.xpm", "textures/HUD/HUD_char_state1_left.xpm", "textures/HUD/HUD_char_state1_right.xpm", 0};
	result = new_anim("state_1", anim, 1, vec2(0, 0), mlx);
	result->loop = TRUE;
	mlx->HUD_CHAR = new_animation_player(result, vec2(0, 0));
	char	*anim_state_2[] = {"textures/HUD/HUD_char_state2_neutral.xpm", "textures/HUD/HUD_char_state2_neutral.xpm", "textures/HUD/HUD_char_state2_frown.xpm", 0};
	result_state_2 = new_anim("state_2", anim_state_2, 1, vec2(0, 0), mlx);
	result_state_2->loop = TRUE;
	add_animation(mlx->HUD_CHAR, result_state_2);
	char	*anim_state_3[] = {"textures/HUD/HUD_char_state3_neutral.xpm", "textures/HUD/HUD_char_state3_neutral.xpm", "textures/HUD/HUD_char_state3_left.xpm", "textures/HUD/HUD_char_state3_right.xpm", 0};
	result_state_3 = new_anim("state_3", anim_state_3, 2, vec2(0, 0), mlx);
	result_state_3->loop = TRUE;
	add_animation(mlx->HUD_CHAR, result_state_3);
}
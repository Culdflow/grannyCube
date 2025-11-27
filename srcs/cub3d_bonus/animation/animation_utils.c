/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpecquer <jpecquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:59:09 by jpecquer          #+#    #+#             */
/*   Updated: 2025/11/26 18:00:28 by jpecquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/animation.h"

void	add_animation(t_animation_player *player, t_animation *anim)
{
	t_animation	*last_anim;

	last_anim = anim_get_last(player->anim_list);
	last_anim->next = anim;
}

void	switch_anim(t_animation_player *player, char *tag)
{
	t_animation	*anim;

	if (ft_strncmp(tag, player->current_anim->anim_tag, ft_strlen(tag)) == 0)
		return ;
	printf("looking for tag %s\n", tag);
	anim = get_anim_with_tag(player->anim_list, tag);
	if (anim)
		player->current_anim = anim;
}

void	free_anim(char **anim)
{
	int		i;

	i = 0;
	while (anim[i] != NULL)
	{
		free(anim[i]);
		i++;
	}
	free(anim);
	anim = NULL;
}

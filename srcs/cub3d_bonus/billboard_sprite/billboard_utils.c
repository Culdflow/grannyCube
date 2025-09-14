/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   billboard_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:17:29 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/14 23:17:45 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	trig_get_angle(int adj, int hyp)
{
	int	other_angle;

	other_angle = acos(adj / hyp);
	return (360 - 90 - other_angle);
}

int	check_is_angle_in_player_view(int angle, int fov, int player_angle)
{
	if (player_angle + (fov / 2) >= angle && player_angle - (fov / 2) <= angle)
		return (TRUE);
	return (FALSE);
}

float	get_percent_billboard_from_view(int angle, int fov, int player_angle)
{
	int		percent_angle;
	int		percent;
	float	result;

	percent_angle = angle - (player_angle - (fov / 2));
	percent = 100 / (fov / percent_angle);
	result = (float)percent / 100.0;
	return (result);
}
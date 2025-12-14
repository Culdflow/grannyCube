/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:02:30 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/14 15:13:21 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	rec_pwr(int nb, int pwr)
{
	if (pwr <= 0)
		return (nb);
	return (nb * rec_pwr(nb, pwr - 1));
}

int	rgb_to_hex(char *rgb)
{
	char	**tab;
	int		r;
	int		g;
	int		b;

	tab = ft_split(rgb, ',');
	r = ft_atoi(tab[0]) / 16;
	g = ft_atoi(tab[1]) / 16;
	b = ft_atoi(tab[2]);
	ft_free_tab(tab);
	return ((r * rec_pwr(16, 4)) + (g * rec_pwr(16, 2)) + b);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

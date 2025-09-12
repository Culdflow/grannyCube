/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:56:16 by dfeve             #+#    #+#             */
/*   Updated: 2025/09/12 02:43:10 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

float	ft_fabsf(float nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

float	ft_fmodulf(float nb, float modul)
{
	int	nb_div;

	nb_div = 0;
	if (nb >= modul)
	{
		nb_div = (nb / modul);
		return (nb - (nb_div * modul));
	}
	return (nb);
}

float	ft_fclampf(float *nb, float min, float max)
{
	if (min > max)
		return (0);
	if (*nb < min)
	{
		*nb = min;
		return (-1);
	}
	else if (*nb > max)
	{
		*nb = max;
		return (-1);
	}
	return (0);
}

int	rec_pwr(int nb, int pwr)
{
	if (pwr <= 0)
		return (nb);
	return(nb * rec_pwr(nb, pwr - 1));
}

int	rgb_to_hex(char *rgb)
{
	char **tab;
	int	r;
	int	g;
	int	b;

	printf("color = %s\n", rgb);
	tab = ft_split(rgb, ',');
	r = ft_atoi(tab[0]) / 16;
	g = ft_atoi(tab[1]) / 16;
	b = ft_atoi(tab[2]);
	printf("red = %d green = %d blue = %d\n", r, g, b);
	ft_free_tab(tab);
	return ((r * rec_pwr(16, 4)) + (g * rec_pwr(16, 2)) + b);
}

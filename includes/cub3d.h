/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdessm <mabdessm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:58:24 by mabdessm          #+#    #+#             */
/*   Updated: 2025/06/03 10:46:41 by mabdessm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include "level_editor.h"
# include "utils.h"

typedef struct s_data
{
	char		**map;
	char		*path_to_the_north_texture;
	char		*path_to_the_south_texture;
	char		*path_to_the_west_texture;
	char		*path_to_the_east_texture;
	char		*floor_color;
	char		*ceiling_color;
	int			invalid_floor_color;
	char		**seperated_floor_color;
	char		**seperated_ceiling_color;
	int			number_of_no;
	int			number_of_so;
	int			number_of_we;
	int			number_of_ea;
	int			number_of_f;
	int			number_of_c;
	int			number_of_players;
}				t_data;

#endif
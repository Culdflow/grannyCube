/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:52:19 by dfeve             #+#    #+#             */
/*   Updated: 2025/12/12 19:53:04 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/directories.h"

void	free_dir_files(t_dir_files *files)
{
	t_dir_files	*cursor;
	t_dir_files	*tmp;

	cursor = files;
	while (cursor)
	{
		tmp = cursor->next;
		free(cursor->name);
		free(cursor);
		cursor = tmp;
	}
}

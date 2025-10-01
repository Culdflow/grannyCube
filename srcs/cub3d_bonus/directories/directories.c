/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:50:57 by dfeve             #+#    #+#             */
/*   Updated: 2025/10/01 19:25:54 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/directories.h"

t_dir_files	*new_dir_file(file_type type, char *name, int on_cursor, t_dir_files *prev)
{
	t_dir_files	*result;

	result = calloc(1, sizeof(t_dir_files));
	result->name = name;
	result->type = type;
	result->status = NOT_SELECTED;
	result->on_cursor = on_cursor;
	result->prev = prev;
	result->next = NULL;
	return (result);
}

void	add_to_dir_list(t_dir_files **list, file_type type, char *name)
{
	t_dir_files	*cursor;

	cursor = *list;
	if (!cursor)
	{
		*list = new_dir_file(type, name, TRUE, NULL);
		return ;
	}
	while (cursor && cursor->next)
		cursor = cursor->next;
	cursor->next = new_dir_file(type, name, FALSE, cursor);
}

t_dir_files	*get_files_from_dir(char *dir)
{
	DIR				*directories;
	struct dirent	*entry;
	t_dir_files		*result;

	result = NULL;
	directories = opendir(dir);
	if (directories == NULL)
	{
		printf("directory not valid\n");
		return (NULL);
	}
	while ((entry = readdir(directories)) != NULL)
	{
		if (entry->d_type == 8)
			add_to_dir_list(&result, T_FILE, entry->d_name);
		else
			add_to_dir_list(&result, T_DIRECTORY, entry->d_name);
	}
	return (result);
}

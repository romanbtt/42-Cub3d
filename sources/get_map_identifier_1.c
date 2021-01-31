/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_identifier_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:09:15 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 16:56:49 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function get the path of the north's texture.
** If the first 3 char are not "NO ", or the path already exist,
** then we return an error.
** We get rid of all the spaces before the path.
** If the path doesn't start with "./", then we return an error.
** We create an **array to store everything in the line separate with spaces.
** If there not array[0] or there is an array[1], we return an error.
** Then we duplicate the line inside the variable text_no.
*/

void	identifier_n(t_struct *cub, t_map *map, char *line)
{
	int i;

	i = 0;
	if (line[i++] != 'N' || line[i++] != 'O' ||
	line[i++] != ' ' || map->text_no)
		exit_faillure(cub, "Could't get the north's texture.");
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '.' || line[i + 1] != '/')
		exit_faillure(cub, "Could't get the north's texture.");
	cub->buff_id.array_no = ft_split_isspace(line + i);
	if (!cub->buff_id.array_no[0] || cub->buff_id.array_no[1])
		exit_faillure(cub, "Could't get the north's texture.");
	map->text_no = ft_strdup(line + i);
}

/*
** This function get the path of the south's texture.
** If the first 3 char are not "SO ", or the path already exist,
** then we return an error.
** We get rid of all the spaces before the path.
** If the path doesn't start with "./", then we return an error.
** We create an **array to store everything in the line separate with spaces.
** If there not array[0] or there is an array[1], we return an error.
** Then we duplicate the line inside the variable text_so.
*/

void	identifier_so(t_struct *cub, t_map *map, char *line)
{
	int i;

	i = 0;
	if (line[i++] != 'S' || line[i++] != 'O' ||
	line[i++] != ' ' || map->text_so)
		exit_faillure(cub, "Could't get the south's texture.");
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '.' || line[i + 1] != '/')
		exit_faillure(cub, "Could't get the south's texture.");
	cub->buff_id.array_so = ft_split_isspace(line + i);
	if (!cub->buff_id.array_so[0] || cub->buff_id.array_so[1])
		exit_faillure(cub, "Could't get the south's texture.");
	map->text_so = ft_strdup(line + i);
}

/*
** This function get the path of the east's texture.
** If the first 3 char are not "EA ", or the path already exist,
** then we return an error.
** We get rid of all the spaces before the path.
** If the path doesn't start with "./", then we return an error.
** We create an **array to store everything in the line separate with spaces.
** If there not array[0] or there is an array[1], we return an error.
** Then we duplicate the line inside the variable text_ea.
*/

void	identifier_e(t_struct *cub, t_map *map, char *line)
{
	int i;

	i = 0;
	if (line[i++] != 'E' || line[i++] != 'A' ||
	line[i++] != ' ' || map->text_ea)
		exit_faillure(cub, "Could't get the east's texture.");
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '.' || line[i + 1] != '/')
		exit_faillure(cub, "Could't get the east's texture.");
	cub->buff_id.array_ea = ft_split_isspace(line + i);
	if (!cub->buff_id.array_ea[0] || cub->buff_id.array_ea[1])
		exit_faillure(cub, "Could't get the east's texture.");
	map->text_ea = ft_strdup(line + i);
}

/*
** This function get the path of the west's texture.
** If the first 3 char are not "WE ", or the path already exist,
** then we return an error.
** We get rid of all the spaces before the path.
** If the path doesn't start with "./", then we return an error.
** We create an **array to store everything in the line separate with spaces.
** If there not array[0] or there is an array[1], we return an error.
** Then we duplicate the line inside the variable text_we.
*/

void	identifier_w(t_struct *cub, t_map *map, char *line)
{
	int i;

	i = 0;
	if (line[i++] != 'W' || line[i++] != 'E' ||
	line[i++] != ' ' || map->text_we)
		exit_faillure(cub, "Could't get the west's texture.");
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '.' || line[i + 1] != '/')
		exit_faillure(cub, "Could't get the west's texture.");
	cub->buff_id.array_we = ft_split_isspace(line + i);
	if (!cub->buff_id.array_we[0] || cub->buff_id.array_we[1])
		exit_faillure(cub, "Could't get the west's texture.");
	map->text_we = ft_strdup(line + i);
}

/*
** This function get the path of the sprite's texture.
** If the first 2 char are "SO", then we call identifier_so and return.
** If the first 2 char are not "S ", or the path already exist,
** then we return an error.
** We get rid of all the spaces before the path.
** If the path doesn't start with "./", then we return an error.
** We create an **array to store everything in the line separate with spaces.
** If there not array[0] or there is an array[1], we return an error.
** Then we duplicate the line inside the variable text_sp.
*/

void	identifier_s_so(t_struct *cub, t_map *map, char *line)
{
	int i;

	i = 0;
	if (line[0] == 'S' && line[1] == 'O')
	{
		identifier_so(cub, map, line);
		return ;
	}
	if (line[i++] != 'S' || line[i++] != ' ' || map->text_sp)
		exit_faillure(cub, "Could't get the sprite's texture.");
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '.' || line[i + 1] != '/')
		exit_faillure(cub, "Could't get the sprite's texture.");
	cub->buff_id.array_sp = ft_split_isspace(line + i);
	if (!cub->buff_id.array_sp[0] || cub->buff_id.array_sp[1])
		exit_faillure(cub, "Could't get the sprite's texture.");
	map->text_sp = ft_strdup(line + i);
}

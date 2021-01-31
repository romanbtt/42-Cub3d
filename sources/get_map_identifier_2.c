/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_identifier_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:32:11 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:23:36 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function get the color's value of the floor.
** If the first 2 char are "F ", and there is not already a color value,
** We put inside a **buffer the line separate by ','.
** Else, we return an error.
** We parse entirely the line until '\0', and we check if all the char are
** digits, spaces, and commas. We check at the same time if there no more than
** 3 commas in the line. If the condition is not respected, we return an error.
** If array[0] to array[2] are empty or array[3] is not, we return an error.
** If the values are not in the range of 0 to 255, we return an error.
** Then we code the color value in an int.
*/

void	identifier_f(t_struct *cub, t_map *map, char *line)
{
	int i;
	int rgb[3];

	cub->buff_id.nb_comma = 0;
	i = -1;
	if (line[++i] == 'F' && ft_isspace(line[1]) && !map->fl_rgb)
		cub->buff_id.array_f = ft_split(line + 1, ',');
	else
		exit_faillure(cub, "Could't get the floor color values.");
	while (line[++i] != '\0')
	{
		if (line[i] == ',')
			cub->buff_id.nb_comma++;
		if ((!ft_isdigit(line[i]) && !ft_isspace(line[i]) && line[i] != ',') ||
			cub->buff_id.nb_comma == 3)
			exit_faillure(cub, "Could't get the floor color values.");
	}
	if (!cub->buff_id.array_f[0] || !cub->buff_id.array_f[1] ||
	!cub->buff_id.array_f[2] || cub->buff_id.array_f[3])
		exit_faillure(cub, "Could't get the floor color values.");
	put_in_rgb(cub->buff_id.array_f, rgb);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 ||
		rgb[2] < 0 || rgb[2] > 255)
		exit_faillure(cub, "Could't get the floor color values.");
	map->fl_rgb = (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

/*
** This function get the color's value of the ceiling.
** If the first 2 char are "C ", and there is not already a color value,
** We put inside a **buffer the line separate by ','.
** Else, we return an error.
** We parse entirely the line until '\0', and we check if all the char are
** digits, spaces, and commas. We check at the same time if there no more than
** 3 commas in the line. If the condition is not respected, we return an error.
** If array[0] to array[2] are empty or array[3] is not, we return an error.
** If the values are not in the range of 0 to 255, we return an error.
** Then we code the color value in an int.
*/

void	identifier_c(t_struct *cub, t_map *map, char *line)
{
	int i;
	int rgb[3];

	cub->buff_id.nb_comma = 0;
	i = -1;
	if (line[++i] == 'C' && ft_isspace(line[1]) && !map->ceil_rgb)
		cub->buff_id.array_c = ft_split(line + 1, ',');
	else
		exit_faillure(cub, "Could't get the ceiling color values.");
	while (line[++i] != '\0')
	{
		if (line[i] == ',')
			cub->buff_id.nb_comma++;
		if ((!ft_isdigit(line[i]) && !ft_isspace(line[i]) && line[i] != ',') ||
			cub->buff_id.nb_comma == 3)
			exit_faillure(cub, "Could't get the ceiling color values.");
	}
	if (!cub->buff_id.array_c[0] || !cub->buff_id.array_c[1] ||
	!cub->buff_id.array_c[2] || cub->buff_id.array_c[3])
		exit_faillure(cub, "Could't get the ceiling color values.");
	put_in_rgb(cub->buff_id.array_c, rgb);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 ||
		rgb[2] < 0 || rgb[2] > 255)
		exit_faillure(cub, "Could't get the ceiling color values.");
	map->ceil_rgb = (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

/*
** This function get the resolution.
** If the first 2 char are "R ", and there is not already a resolution value,
** We put inside a **buffer the line separate by ' '.
** Else, we return an error.
** We parse entirely the line until '\0', and we check if all the char are
** digits and spaces. If the condition is not respected, we return an error.
** If array[1] is empty or array[2] is not, we return an error.
** Then we put inside the variables width and height, the corresponding value.
*/

void	identifier_r(t_struct *cub, t_map *map, char *line)
{
	int i;

	i = -1;
	if (line[++i] == 'R' && ft_isspace(line[1]) && !map->width)
		cub->buff_id.array_r = ft_split_isspace(line + 1);
	else
		exit_faillure(cub, "Could't get the resolution values.");
	while (line[++i] != '\0')
	{
		if (!ft_isdigit(line[i]) && !ft_isspace(line[i]))
			exit_faillure(cub, "Could't get the resolution values.");
	}
	if (!cub->buff_id.array_r[1] || cub->buff_id.array_r[2])
		exit_faillure(cub, "Could't get the resolution values.");
	map->width = ft_atoi(cub->buff_id.array_r[0]);
	map->height = ft_atoi(cub->buff_id.array_r[1]);
}

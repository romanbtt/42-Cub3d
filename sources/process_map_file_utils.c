/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_file_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:47:00 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:09:14 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function checks if the line is empty or not.
** We get rid of all the spaces and check if there is a '\n' or '\0' at the end.
** If yes, it returns true. Otherwise, it return false.
*/

bool	is_empty_line(char *line)
{
	int i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (true);
	return (false);
}

/*
** This function checks if the line is a line describing the map.
**We get rid of all the spaces and check if there is a '1' or '0' at the
** beginning of the line.
** If yes, it returns true. Otherwise, it return false.
*/

bool	is_line_map(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (true);
	return (false);
}

/*
** This function check if the char passed in parameter is part of one of the
** identifiers.
** Here we put as well the minuscules identifier to not fall in this case
** because we want to display the error inside the corresponding function.
** If an identifier is founded, we return true, otherwise we return false.
*/

bool	is_map_identifier(char c)
{
	if ((c == 'N' || c == 'n') ||
	(c == 'S' || c == 's') ||
	(c == 'W' || c == 'w') ||
	(c == 'E' || c == 'e') ||
	(c == 'R' || c == 'r') ||
	(c == 'F' || c == 'f') ||
	(c == 'C' || c == 'c'))
		return (true);
	return (false);
}

/*
** If the is_line_map return true and an identifier is missing.
** Then we store inside a buffer all the messages of error.
** If there is some messages to display, we call exit_faillure
** to start the process of quitting the program with the buffer in parameter.
*/

bool	is_missing_identifier(t_struct *cub, char *line)
{
	char str[512];

	str[0] = '\0';
	if (is_line_map(line) && !cub->map.width)
		ft_strlcat(str, "Resolution values is missing.\n", 512);
	if (is_line_map(line) && !cub->map.fl_rgb)
		ft_strlcat(str, "Floor color values is missing.\n", 512);
	if (is_line_map(line) && !cub->map.ceil_rgb)
		ft_strlcat(str, "Ceiling color values is missing.\n", 512);
	if (is_line_map(line) && !cub->map.text_no)
		ft_strlcat(str, "North's path texture is missing.\n", 512);
	if (is_line_map(line) && !cub->map.text_so)
		ft_strlcat(str, "South's path texture is missing.\n", 512);
	if (is_line_map(line) && !cub->map.text_ea)
		ft_strlcat(str, "East's path texture is missing.\n", 512);
	if (is_line_map(line) && !cub->map.text_we)
		ft_strlcat(str, "West's path texture is missing.\n", 512);
	if (is_line_map(line) && !cub->map.text_sp)
		ft_strlcat(str, "Sprite's path texture is missing.\n", 512);
	if (str[0])
		exit_faillure(cub, str);
	return (false);
}

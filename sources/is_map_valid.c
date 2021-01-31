/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:22:42 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:00:00 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function check if a char is allowed.
** It returns true if yes, otherwise it returns false.
*/

static bool		is_char_allowed(char c)
{
	if (!c)
		return (0);
	if (ft_strchr("012NSEW", c))
		return (true);
	return (false);
}

/*
** This function check if the XY position provided by the parameter
** is correct to have a valid map.
** The first condition checks the position in case of a first, last row,
** or in case of first, last column. In this case, we check if the char at
** the position XY is a '1' or ' '. If not, we return an error.
** The second condition checks the position of all the rest. (inside the map).
** We check with the help of the function is_char_allowed the eight sides
** of the position provide in parameter. If one of them is not allowed, then
** we return an error.
*/

static void		check_sides_map(t_struct *cub, int row, int col,
	int curr_col_len)
{
	if (((row == 0 || row == cub->map.row_len - 1) || (col == 0 ||
	col == curr_col_len - 1)) &&
	(!(ft_strchr("1 ", cub->map.map_2d[row][col]))))
		exit_faillure(cub, "The map is not valid.\n");
	else if ((row > 0 && row < cub->map.row_len - 1) &&
	(col > 0 && col < curr_col_len - 1) &&
	(ft_strchr("02NSWE", cub->map.map_2d[row][col])) &&
	((!(is_char_allowed(cub->map.map_2d[row - 1][col]))) ||
	(!(is_char_allowed(cub->map.map_2d[row + 1][col]))) ||
	(!(is_char_allowed(cub->map.map_2d[row][col + 1]))) ||
	(!(is_char_allowed(cub->map.map_2d[row][col - 1]))) ||
	(!(is_char_allowed(cub->map.map_2d[row - 1][col - 1]))) ||
	(!(is_char_allowed(cub->map.map_2d[row + 1][col - 1]))) ||
	(!(is_char_allowed(cub->map.map_2d[row - 1][col + 1]))) ||
	(!(is_char_allowed(cub->map.map_2d[row + 1][col + 1])))))
		exit_faillure(cub, "The map is not valid.\n");
}

/*
** This function checks if an entire map is valid or not.
** We split by '\n', the map_1d buffer inside an **array map_2d buffer.
** Then for each char of the map, we check if the char is allowed to be in
** this particular position with the help of check_sides_map (same file).
** We call get_info_player to get the player position.
** We count the number of sprites on the map.
** We update the variable that store the maximum of column founded.
** When the loop reached his end, we check if the player position was set.
** If not, we return an error.
*/

void			is_map_valid(t_struct *cub, t_map *map, t_player *pl)
{
	int row;
	int col;
	int curr_col_len;

	row = 0;
	map->map_2d = ft_split(map->map_1d, '\n');
	ft_strdel(&map->map_1d);
	while (row < map->row_len)
	{
		col = 0;
		curr_col_len = ft_strlen(map->map_2d[row]);
		while (col < curr_col_len)
		{
			check_sides_map(cub, row, col, curr_col_len);
			get_info_player(cub, pl, row, col);
			if (map->map_2d[row][col] == '2')
				map->sp_qty++;
			col++;
		}
		row++;
		if (curr_col_len > map->col_len)
			map->col_len = curr_col_len;
	}
	if (!pl->pos.x || !pl->pos.y)
		exit_faillure(cub, "Player position is not set on the map.\n");
}

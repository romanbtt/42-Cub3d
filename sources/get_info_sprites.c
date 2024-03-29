/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:41:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 16:55:03 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function get all the sprites position in the map.
** If the XY position in the map is equal to '2'.
** Then we saved the position in the sprites struct.
** Each sprite owns his proper structure.
*/

void		get_info_sprites(t_struct *cub)
{
	int i;
	int row;
	int col;
	int curr_col_len;

	i = 0;
	row = 0;
	while (row < cub->map.row_len)
	{
		col = 0;
		curr_col_len = ft_strlen(cub->map.map_2d[row]);
		while (col < curr_col_len)
		{
			if (cub->map.map_2d[row][col] == '2')
			{
				cub->sprites[i].pos.x = (col + 0.5) * cub->map.tile_size;
				cub->sprites[i].pos.y = (row + 0.5) * cub->map.tile_size;
				i++;
			}
			col++;
		}
		row++;
	}
}

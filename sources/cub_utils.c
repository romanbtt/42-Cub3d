/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:21:02 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 16:51:00 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function will calculate which tile_size we need to use depends of
** size of the smallest texture.
** We use a bubble sort to sort all the size height and width of each texture.
** Then we select the smallest value to assign to tile_size.
*/

int		calc_size_tile(t_struct *cub)
{
	int i;
	int j;
	int tmp;

	i = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 7 - i)
		{
			if (cub->text.res_text[j] > cub->text.res_text[j + 1])
			{
				tmp = cub->text.res_text[j];
				cub->text.res_text[j] = cub->text.res_text[j + 1];
				cub->text.res_text[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (cub->text.res_text[0]);
}

/*
** This function calculates the distance between two points on an XY map.
*/

float	dist_btw_pts(float x1, float x2, float y1, float y2)
{
	float	distance;

	distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return (distance);
}

/*
** This function keeps an angle between 0 and 2 * PI.
*/

float	normalize_angle(float angle)
{
	angle = remainderf(angle, 2 * PI);
	if (angle < 0)
		angle = 2 * PI + angle;
	return (angle);
}

/*
** This function checks if there is a wall (1) at an XY position.
** We first check if the coordinate is out of the screen.
** The we multiply by the tile_size to check if the position in the map
** is equal at '1'.
*/

bool	is_wall_at(t_map *map, int x, int y)
{
	int	row;
	int	col;

	if (x < 0 || x >= map->tile_size * map->width ||
	y < 0 || y >= map->tile_size * map->height)
		return (true);
	row = y / map->tile_size;
	col = x / map->tile_size;
	return (map->map_2d[row][col] == '1');
}

/*
** This function puts a string that contains a color value inside an int array.
*/

void	put_in_rgb(char **array, int rgb[3])
{
	int i;

	i = 0;
	while (i < 3)
	{
		ft_delspace(array[i]);
		rgb[i] = ft_atoi(array[i]);
		i++;
	}
}

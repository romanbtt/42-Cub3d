/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_projection_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 22:18:20 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:16:12 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function display the wall with the texture.
** Row is assigned to the value of top_strip.
** Ofst.X/Y (offset) is the XY coordinate of the pixel that we need to print
** in the image texture.
** We find ofst.x depending on if the hit was vertical or not. Then we do
** a modulo of ray[col].hit.X/Y by tile_size.
** And multiply the ofst.X by the width texture divide by tile_size.
** Then for each row until btm_strp is reached, we need to calculate the
** top_distance and ofst.Y
** Top_dist is equal to the current # row + wall_height / 2 - res height / 2
** ofst.Y is equal to top_dist * texture height / proj_wall_height.
** We call pick_pixel to pick the pixel inside the texture's image.
** Then we insert this pixel directly inside the image of our window.
*/

void	print_wall(t_struct *cub, t_wall *wall, int col)
{
	int				row;
	unsigned int	color;

	row = wall->top_strp;
	if (cub->ray[col].hit_vert)
		wall->ofst_x = (int)cub->ray[col].hit.y % cub->map.tile_size;
	else
		wall->ofst_x = (int)cub->ray[col].hit.x % cub->map.tile_size;
	wall->ofst_x *= cub->text.curr.width / cub->map.tile_size;
	while (row < wall->btm_strp)
	{
		wall->top_dist = row + (wall->proj_wall_height / 2) -
		(cub->map.height / 2);
		wall->ofst_y = wall->top_dist * (cub->text.curr.height /
			wall->proj_wall_height);
		color = pick_pixel(&cub->text.curr, wall->ofst_x, wall->ofst_y);
		insert_pixel(&cub->img, col, row, color);
		row++;
	}
}

/*
** This function display the ceiling color.
** We start at 0, Then for each row until top_strip is reached. (top of wall)
** We insert the pixel at COL ROW coordinate of the color of the ceiling.
*/

void	print_ceiling(t_struct *cub, t_wall *wall, int col)
{
	int row;

	row = 0;
	while (row < wall->top_strp)
	{
		insert_pixel(&cub->img, col, row, cub->map.ceil_rgb);
		row++;
	}
}

/*
** This function display the floor color.
** Row is assigned to the btm_strip value (bottom of wall).
** Then for each row until btm_strip is reached.
** We insert the pixel at COL ROW coordinate of the color of the floor.
*/

void	print_floor(t_struct *cub, t_wall *wall, int col)
{
	int row;

	row = wall->btm_strp;
	while (row < cub->map.height)
	{
		insert_pixel(&cub->img, col, row, cub->map.fl_rgb);
		row++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_projection_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 21:16:01 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:15:14 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function choose which texture need to be load depending on where
** the ray is facing and if the hit was vertical or not.
*/

static void	select_texture(t_texture *text, t_ray *ray)
{
	if (ray->isray_up && !ray->hit_vert)
		text->curr = text->no;
	else if (ray->isray_down && !ray->hit_vert)
		text->curr = text->so;
	else if (ray->isray_right && ray->hit_vert)
		text->curr = text->ea;
	else if (ray->isray_left && ray->hit_vert)
		text->curr = text->we;
}

/*
** This function calculate the height of the wall and where it begins
** and where it stops. Perp_dist is calculated to get rid of the fisheye
** effect that happens.
** Top_strp is where the wall begins. It is calculated with the height
** resolution / 2 - the height of a wall / 2.
** Btm_strp is where the wall stops. It is calculated with the height
** resolution / 2 + the height of a wall / 2.
*/

static void	calc_wall_height(t_struct *cub, t_wall *wall, int col)
{
	wall->perp_dist = cub->ray[col].dist * cos(cub->ray[col].ray_angle -
		cub->player.rot_angle);
	wall->proj_wall_height = (cub->map.tile_size / wall->perp_dist) *
		wall->dist_proj_plane;
	wall->top_strp = (cub->map.height / 2) - (int)(wall->proj_wall_height / 2);
	if (wall->top_strp < 0)
		wall->top_strp = 0;
	wall->btm_strp = (cub->map.height / 2) + (int)(wall->proj_wall_height / 2);
	if (wall->btm_strp > cub->map.height)
		wall->btm_strp = cub->map.height;
}

/*
** This function handle the print projection of the wall, ceiling, and floor.
** For each ray until the width resolution is reach we call :
** The engine function that calculates the height of the wall.
** Print_ceiling that will display the ceiling color.
** Select_texture that will choose which texture to load.
** Print_wall that will display the wall with texture.
** Print_floor that will display the floor color.
** Then col is incremented by one.
*/

void		render_projection(t_struct *cub)
{
	int		col;
	t_wall	wall;

	col = 0;
	wall.dist_proj_plane = (cub->map.width / 2) / tan(FOV / 2);
	while (col < cub->map.width)
	{
		calc_wall_height(cub, &wall, col);
		print_ceiling(cub, &wall, col);
		select_texture(&cub->text, &cub->ray[col]);
		print_wall(cub, &wall, col);
		print_floor(cub, &wall, col);
		col++;
	}
}

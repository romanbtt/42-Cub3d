/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_horz.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 21:03:47 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:11:47 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function increment with a position with a variable calculated before
** until it reach a wall at the end of the window.
** We start a loop until we hit a wall or we are at the limit of the window.
** Each time, we assign the value of intcp_X/Y (intercept) to chk_X/Y (check).
** Then we check if there is a wall at the position of XY of chk.
** If there is, we assign the value of the position XY of intcp to the variable
** hit, set was_hit at true, and then exit the function.
** If is_wall_at return false, we add the value of step XY to the variable
** intcp XY. It is in this step that we increment to position to check if
** there is a wall or not.
*/

static void	increment_horz(t_map *map, t_ray *ray, t_helper_ray *horz)
{
	int max_width;
	int max_height;

	max_width = map->tile_size * map->col_len;
	max_height = map->tile_size * map->row_len;
	while (horz->intcp.x >= 0 && horz->intcp.x <= max_width &&
		horz->intcp.y >= 0 && horz->intcp.y <= max_height)
	{
		horz->chk.x = horz->intcp.x;
		if (ray->isray_up)
			horz->chk.y = horz->intcp.y - 1;
		else
			horz->chk.y = horz->intcp.y;
		if (is_wall_at(map, horz->chk.x, horz->chk.y))
		{
			horz->was_hit = true;
			horz->hit.x = horz->intcp.x;
			horz->hit.y = horz->intcp.y;
			break ;
		}
		horz->intcp.x += horz->step.x;
		horz->intcp.y += horz->step.y;
	}
}

/*
** This function calculate step.X and step.Y that will be use in increment_horz
** right after to increment and find a wall.
** We first need to find the first value of intcp.X and intcp.Y, where we begin
** to increment.
** Then we calculate step.X and step.Y, which will be use to know of how many
** pixel, we need to increment intcp.X/Y.
** Step.Y is easy to discover since it is equal to the tile_size.
** Step.X use some trigonometry to find his value. H = O / T
*/

void		horizontal_casting(t_map *map, t_ray *ray, t_helper_ray *horz,
	t_player *pl)
{
	horz->intcp.y = floor(pl->pos.y / map->tile_size) * map->tile_size;
	if (ray->isray_down)
		horz->intcp.y += map->tile_size;
	horz->intcp.x = pl->pos.x + (horz->intcp.y - pl->pos.y) /
		tan(ray->ray_angle);
	horz->step.y = map->tile_size;
	if (ray->isray_up)
		horz->step.y *= -1;
	horz->step.x = map->tile_size / tan(ray->ray_angle);
	if (ray->isray_left && horz->step.x > 0)
		horz->step.x *= -1;
	if (ray->isray_right && horz->step.x < 0)
		horz->step.x *= -1;
	increment_horz(map, ray, horz);
}

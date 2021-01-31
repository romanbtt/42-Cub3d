/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_vert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 21:03:47 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:12:22 by romanbtt         ###   ########.fr       */
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

static void	increment_vert(t_map *map, t_ray *ray, t_helper_ray *vert)
{
	int max_width;
	int max_height;

	max_width = map->tile_size * map->col_len - 1;
	max_height = map->tile_size * map->row_len - 1;
	while (vert->intcp.x >= 0 && vert->intcp.x <= max_width &&
		vert->intcp.y >= 0 && vert->intcp.y <= max_height)
	{
		vert->chk.y = vert->intcp.y;
		if (ray->isray_left)
			vert->chk.x = vert->intcp.x - 1;
		else
			vert->chk.x = vert->intcp.x;
		if (is_wall_at(map, vert->chk.x, vert->chk.y))
		{
			vert->was_hit = true;
			vert->hit.x = vert->intcp.x;
			vert->hit.y = vert->intcp.y;
			break ;
		}
		vert->intcp.x += vert->step.x;
		vert->intcp.y += vert->step.y;
	}
}

/*
** This function calculate step.X and step.Y that will be use in increment_vert
** right after to increment and find a wall.
** We first need to find the first value of intcp.X and intcp.Y, where we begin
** to increment.
** Then we calculate step.X and step.Y, which will be use to know of how many
** pixel, we need to increment intcp.X/Y.
** Step.X is easy to discover since it is equal to the tile_size.
** Step.Y use some trigonometry to find his value. H = O / T
*/

void		vertical_casting(t_map *map, t_ray *ray, t_helper_ray *vert,
	t_player *pl)
{
	vert->intcp.x = floor(pl->pos.x / map->tile_size) * map->tile_size;
	if (ray->isray_right)
		vert->intcp.x += map->tile_size;
	vert->intcp.y = pl->pos.y + (vert->intcp.x - pl->pos.x) *
		tan(ray->ray_angle);
	vert->step.x = map->tile_size;
	if (ray->isray_left)
		vert->step.x *= -1;
	vert->step.y = map->tile_size * tan(ray->ray_angle);
	if (ray->isray_up && vert->step.y > 0)
		vert->step.y *= -1;
	if (ray->isray_down && vert->step.y < 0)
		vert->step.y *= -1;
	increment_vert(map, ray, vert);
}

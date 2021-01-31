/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:06:57 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:41:18 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function choose the shortest distance between two value
** If vertical hit distance is shorter than horizontal hit distance.
** Then we assign the ray's values with the values of vertical.
** Otherwise, we assign the ray's values with the values of horizontal.
*/

static void	select_shortest(t_ray *ray, t_helper_ray *horz, t_helper_ray *vert)
{
	if (vert->dist < horz->dist)
	{
		ray->dist = vert->dist;
		ray->hit.x = vert->hit.x;
		ray->hit.y = vert->hit.y;
		ray->hit_vert = true;
	}
	else
	{
		ray->dist = horz->dist;
		ray->hit.x = horz->hit.x;
		ray->hit.y = horz->hit.y;
		ray->hit_horz = true;
	}
}

/*
** This function is an intermediate function to select the shortest hit
** distance between two points. It create two helper two determine the hit
** distance. Then call the two functions horizontal_casting and
** vertical_casting who will proceed to the calculation.
** Then we store inside the variables dist of horz and vert, the result of
** the function dist_btw_pts.
** Then we select the shortest distance with the help of select_shortest.
*/

static void	casting_ray(t_map *map, t_ray *ray, t_player *pl)
{
	t_helper_ray horz;
	t_helper_ray vert;

	horz = (t_helper_ray) {{0}, {0}, {0}, {0}, 0, 0};
	vert = (t_helper_ray) {{0}, {0}, {0}, {0}, 0, 0};
	ray->isray_down = ray->ray_angle > 0 && ray->ray_angle < PI;
	ray->isray_up = !ray->isray_down;
	ray->isray_right = ray->ray_angle < 0.5 * PI || ray->ray_angle > 1.5 * PI;
	ray->isray_left = !ray->isray_right;
	horizontal_casting(map, ray, &horz, pl);
	vertical_casting(map, ray, &vert, pl);
	if (horz.was_hit == true)
		horz.dist = dist_btw_pts(pl->pos.x, horz.hit.x, pl->pos.y, horz.hit.y);
	else
		horz.dist = FLT_MAX;
	if (vert.was_hit)
		vert.dist = dist_btw_pts(pl->pos.x, vert.hit.x, pl->pos.y, vert.hit.y);
	else
		vert.dist = FLT_MAX;
	select_shortest(ray, &horz, &vert);
}

/*
** This function calls for each ray until the width value of the window
** is reached. (One ray per pixel) --> width 1920 px = 1920 rays.
** Each time, a new struct ray is initialize to 0.
** We keep the ray_angle in a range of 0 and 2 * PI.
** We call casting_ray to proceed to the calculation.
** ray_angle is incremented with the FOV / window width to determinate of
** how many degrees we need incremented the angle.
** Stripe_id is incremented by one to go to the next ray.
*/

void		raycasting(t_struct *cub)
{
	float	ray_angle;
	int		stripe_id;
	t_ray	*ray;

	stripe_id = 0;
	ray_angle = cub->player.rot_angle - (FOV / 2);
	while (stripe_id < cub->map.width)
	{
		cub->ray[stripe_id] = (t_ray) {{0}, 0, 0, 0, 0, 0, 0, 0, 0};
		ray = &cub->ray[stripe_id];
		ray->ray_angle = normalize_angle(ray_angle);
		casting_ray(&cub->map, ray, &cub->player);
		ray_angle += FOV / cub->map.width;
		stripe_id++;
	}
}

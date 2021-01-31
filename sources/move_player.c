/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:09:06 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:25:27 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function check if there is a collision at the XY position passed in
** parameter. We need to check the round value of this position. So we need
** to floor these values before checking them.
** We check if these values are out of the range of the map.
** If yes, we return true.
** Then we check if there is a '1' or '2' (Wall or sprite) at the XY position
** calculated with the floor function. And return true or false depending if
** there is or not.
*/

static bool		is_collision_at(t_map *map, float x, float y)
{
	int chk_x;
	int chk_y;

	chk_x = floor(x / map->tile_size);
	chk_y = floor(y / map->tile_size);
	if (chk_y >= map->row_len || chk_x >= (int)ft_strlen(map->map_2d[chk_y]))
		return (true);
	return (ft_strchr("12", map->map_2d[chk_y][chk_x]));
}

/*
** This function check is an intermediate step before checking if there is
** a possible collision. We add padding to these XY positions to not stop
** right in the wall or the sprite but a little bit before.
*/

static bool		check_collision(t_map *map, float x, float y)
{
	if (!is_collision_at(map, x, y) &&
	!is_collision_at(map, x, y - 10) &&
	!is_collision_at(map, x - 10, y) &&
	!is_collision_at(map, x - 10, y - 10) &&
	!is_collision_at(map, x, y + 10) &&
	!is_collision_at(map, x + 10, y) &&
	!is_collision_at(map, x + 10, y + 10))
		return (false);
	return (true);
}

/*
** This function proceed to all the calculations to move the player.
** We update the rotation of the player in a direction or in the other
** depending of which key was pressed (right-left) and with the rotation speed.
** We keep the angle in the range of 0 - 2 * PI with normalize_angle.
** Move_step and side_step are calculated in the same way as rotation angle.
** Then we need to calculate the new position of the player.
** To obtain the X coordinate. We calculated the cosinus of the rotation time
** move_step. Then we add the current X position of the player.
** Same thing for the Y coordinate but with sinus this time.
** Then at the end, we check if there a collision at this new XY coordinate.
** We do the same thing to calculate the new position of the player when we
** pressed the keys for a lateral movement. Unless in this case we need to
** modify the rotation angle by adding half of PI and use side_step.
*/

void			move_player(t_map *map, t_player *pl)
{
	float	move_step;
	float	side_step;
	t_pos	new;

	pl->rot_angle += pl->turn_direction * pl->rot_speed;
	pl->rot_angle = normalize_angle(pl->rot_angle);
	move_step = pl->walk_fwd_bwd * pl->walk_speed;
	side_step = pl->walk_rgt_lft * pl->walk_speed;
	new.x = pl->pos.x + cos(pl->rot_angle) * move_step;
	new.y = pl->pos.y + sin(pl->rot_angle) * move_step;
	if (check_collision(map, new.x, new.y) == false)
		pl->pos = new;
	new.x = pl->pos.x + cos(pl->rot_angle + 0.5 * PI) * side_step;
	new.y = pl->pos.y + sin(pl->rot_angle + 0.5 * PI) * side_step;
	if (check_collision(map, new.x, new.y) == false)
		pl->pos = new;
}

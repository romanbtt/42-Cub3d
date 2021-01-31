/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:25:06 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 16:54:50 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function initialize the rotation angle depending on what was assigned
** in the map file.
*/

static void	get_player_angle(t_player *pl, char angle)
{
	if (angle == 'N')
		pl->rot_angle = 1.5 * PI;
	else if (angle == 'S')
		pl->rot_angle = 0.5 * PI;
	else if (angle == 'E')
		pl->rot_angle = 2 * PI;
	else if (angle == 'W')
		pl->rot_angle = PI;
}

/*
** This function check if there is an "NSWE" identifiers at the XY position.
** If yes, the player position is saved. And we add a 0.5 to set the player
** at the middle of a cube.
** We call get get_player_angle (same file) to get the orientation angle.
** We check at the same time, if the position is set more than once and return
** an error if it is the case.
*/

void		get_info_player(t_struct *cub, t_player *pl, int row, int col)
{
	if (ft_strchr("NSWE", cub->map.map_2d[row][col]))
	{
		if (!pl->pos.x)
		{
			pl->pos.x = col + 0.5;
			pl->pos.y = row + 0.5;
			get_player_angle(pl, cub->map.map_2d[row][col]);
		}
		else
			exit_faillure(cub, "Player position is set more than once.\n");
	}
}

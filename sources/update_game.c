/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:04:31 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:21:26 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function is called inside the mlx loop.
** Each time we update the movement of the player.
** We run our raycasting engine.
** Then we render our projection (Ceiling, wall, floor).
** We render our sprites.
** And finally, we put our image inside the window and synchronize our window.
*/

int	update_game(t_struct *cub)
{
	move_player(&cub->map, &cub->player);
	raycasting(cub);
	render_projection(cub);
	render_sprites(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	mlx_do_sync(cub->mlx);
	return (1);
}

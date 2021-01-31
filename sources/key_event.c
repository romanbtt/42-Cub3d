/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:42:38 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:01:29 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ESC 65307
#define LEFT_ARROW 65361
#define RIGHT_ARROW 65363
#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100

/*
** This function is called when a key is triggered.
** Then, depending on which key was pressed, we execute some action.
** If it is the escape key: We call exit_game to quit the program.
** If it is the right or left arrow: We set turn_direction to 1 or -1.
** If it is the W or S keys: We set walk_fwd_bwd to 1 or -1.
** If it is the D or A keys: We set walk_rgt_lft to 1 or -1.
*/

static int	trigger_keys(int keycode, t_struct *cub)
{
	if (keycode == ESC)
		exit_game(cub);
	if (keycode == RIGHT_ARROW)
		cub->player.turn_direction = 1;
	if (keycode == LEFT_ARROW)
		cub->player.turn_direction = -1;
	if (keycode == W_KEY)
		cub->player.walk_fwd_bwd = 1;
	if (keycode == S_KEY)
		cub->player.walk_fwd_bwd = -1;
	if (keycode == D_KEY)
		cub->player.walk_rgt_lft = 1;
	if (keycode == A_KEY)
		cub->player.walk_rgt_lft = -1;
	return (0);
}

/*
** This function is called when a key is released.
** Then, depending on which key is release, we set the variable associate
** to this key to 0.
*/

static int	release_keys(int keycode, t_struct *cub)
{
	if (keycode == RIGHT_ARROW)
		cub->player.turn_direction = 0;
	if (keycode == LEFT_ARROW)
		cub->player.turn_direction = 0;
	if (keycode == W_KEY)
		cub->player.walk_fwd_bwd = 0;
	if (keycode == S_KEY)
		cub->player.walk_fwd_bwd = 0;
	if (keycode == A_KEY)
		cub->player.walk_rgt_lft = 0;
	if (keycode == D_KEY)
		cub->player.walk_rgt_lft = 0;
	return (0);
}

/*
** This function is called at each loop to checks if a key is pressed or release
** or the red cross was clicked.
** Then depending on the situation, the right function is called.
*/

void		key_event(t_struct *cub)
{
	mlx_hook(cub->win, 33, (1l << 17), exit_game, cub);
	mlx_hook(cub->win, 2, (1l << 0), trigger_keys, cub);
	mlx_hook(cub->win, 3, (1L << 1), release_keys, cub);
}

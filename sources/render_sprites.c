/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:09:13 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:19:37 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function is used to pick a pixel at XY coordinate inside a sprite's
** image and right after to insert this pixel at XY coordinate inside our
** window image if this pixel is different than 0 (black).
*/

static void	pick_insert_color(t_struct *cub, t_sprites *sp, int x, int y)
{
	int	color;

	color = pick_pixel(&cub->text.sp, x * cub->text.sp.height / sp->size,
	y * cub->text.sp.width / sp->size);
	if (color != 0)
		insert_pixel(&cub->img, sp->ofst_x + x, sp->ofst_y + y, color);
}

/*
** This function is print the sprite's image on the image's window.
** For each y until sp->size is reached;
** We check if the offset.Y + y is in the height window.
** Then for each x until sp->size is reach, we check if offset.x + x
** is int the width window and if ray[offset.x + x].distance is greater
** than the player distance. If yes, we can call pick_insert_color to pick
** and insert the pixel of the sprite's image.
*/

static void	print_sprite(t_struct *cub, int i)
{
	int			x;
	int			y;
	t_sprites	*sp;

	y = 0;
	sp = &cub->sprites[i];
	while (y < sp->size)
	{
		if (sp->ofst_y + y >= 0 && sp->ofst_y + y < cub->map.height)
		{
			x = 0;
			while (x < sp->size)
			{
				if ((sp->ofst_x + x >= 0 && sp->ofst_x + x < cub->map.width) &&
				(cub->ray[sp->ofst_x + x].dist > sp->pl_dist))
					pick_insert_color(cub, sp, x, y);
				x++;
			}
		}
		y++;
	}
}

/*
** This function is used to calculate each sprite.
** For each 'i' until the sprite quantity is reached.
** We calculate the arc tangent of the sprite position Y - player position Y
** and the sprite position X - player position X.
** Then we calculate the distance between the player and the sprite.
** We calculate the size of the sprite.
** Then we calculate the offset X/Y that will be used to pick the right pixel
** inside the sprite's image.
*/

static void	calc_sprites(t_struct *cub)
{
	int			i;
	t_sprites	*sp;
	t_player	*pl;

	i = 0;
	pl = &cub->player;
	while (i < cub->map.sp_qty)
	{
		sp = &cub->sprites[i];
		sp->dir = atan2(sp->pos.y - pl->pos.y, sp->pos.x - pl->pos.x);
		while (sp->dir - pl->rot_angle > PI)
			sp->dir -= 2 * PI;
		while (sp->dir - pl->rot_angle < -PI)
			sp->dir += 2 * PI;
		sp->pl_dist = dist_btw_pts(pl->pos.x, sp->pos.x, pl->pos.y,
			sp->pos.y);
		sp->size = cub->map.width / sp->pl_dist * cub->map.tile_size;
		sp->ofst_y = (cub->map.height / 2) - (sp->size / 2);
		sp->ofst_x = (sp->dir - pl->rot_angle) * cub->map.width / FOV +
			(cub->map.width / 2) - (sp->size / 2);
		i++;
	}
}

/*
** This function sort all the sprites from the closest one to the farthest one.
** We need to do that, because we want to print the closest one first.
** Bubble sort algorithm is used.
*/

static void	sort_sprites(t_struct *cub)
{
	int			i;
	int			j;
	t_sprites	temp;

	i = 0;
	while (i < cub->map.sp_qty)
	{
		j = 0;
		while (j < cub->map.sp_qty - 1)
		{
			if (cub->sprites[j].pl_dist < cub->sprites[j + 1].pl_dist)
			{
				temp = cub->sprites[j];
				cub->sprites[j] = cub->sprites[j + 1];
				cub->sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/*
** This function is used to render all the sprites.
** we first call the engine function calc_sprites to calculate all the sprites.
** Then we call sort_sprites to sort from the closest to the farthest all the
** sprites.
** Then for each sprite, we call the print_sprite function to render
** the sprite.
*/

void		render_sprites(t_struct *cub)
{
	int i;

	i = 0;
	calc_sprites(cub);
	sort_sprites(cub);
	while (i < cub->map.sp_qty)
	{
		print_sprite(cub, i);
		i++;
	}
}

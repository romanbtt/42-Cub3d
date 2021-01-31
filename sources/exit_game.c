/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 23:20:19 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 18:27:36 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function freed all the pointers assigned along the program.
*/

static void	free_textures_1(t_struct *cub)
{
	if (cub->text.no.img)
		mlx_destroy_image(cub->mlx, cub->text.no.img);
	if (cub->text.so.img)
		mlx_destroy_image(cub->mlx, cub->text.so.img);
	if (cub->text.ea.img)
		mlx_destroy_image(cub->mlx, cub->text.ea.img);
	if (cub->text.we.img)
		mlx_destroy_image(cub->mlx, cub->text.we.img);
	if (cub->text.sp.img)
		mlx_destroy_image(cub->mlx, cub->text.sp.img);
	if (cub->map.text_no)
		free(cub->map.text_no);
	if (cub->map.text_so)
		free(cub->map.text_so);
	if (cub->map.text_ea)
		free(cub->map.text_ea);
	if (cub->map.text_we)
		free(cub->map.text_we);
	if (cub->map.text_sp)
		free(cub->map.text_sp);
}

/*
** This function freed all the pointers assigned along the program.
*/

static void	free_textures_2(t_struct *cub)
{
	if (cub->buff_id.array_r)
		free_char_2d(cub->buff_id.array_r);
	if (cub->buff_id.array_c)
		free_char_2d(cub->buff_id.array_c);
	if (cub->buff_id.array_f)
		free_char_2d(cub->buff_id.array_f);
	if (cub->buff_id.array_no)
		free_char_2d(cub->buff_id.array_no);
	if (cub->buff_id.array_so)
		free_char_2d(cub->buff_id.array_so);
	if (cub->buff_id.array_ea)
		free_char_2d(cub->buff_id.array_ea);
	if (cub->buff_id.array_we)
		free_char_2d(cub->buff_id.array_we);
	if (cub->buff_id.array_sp)
		free_char_2d(cub->buff_id.array_sp);
}

/*
** This function print the error message.
** Then it calls exit_game to start the process of exiting the program.
*/

void		exit_faillure(t_struct *cub, char *error)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(error, 1);
	exit_game(cub);
}

/*
** This function freed a pointer of pointer.
*/

void		free_char_2d(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

/*
** This function freed all the pointers assigned along the program.
** And calls the functions to destroy the images and windows.
** Then it calls the function exit to quit the program.
*/

int			exit_game(t_struct *cub)
{
	if (cub->sprites)
		free(cub->sprites);
	if (cub->ray)
		free(cub->ray);
	if (cub->bmp.buff_body)
		free(cub->bmp.buff_body);
	free_textures_1(cub);
	free_textures_2(cub);
	if (cub->map.map_1d)
		free(cub->map.map_1d);
	if (cub->map.map_2d)
		free_char_2d(cub->map.map_2d);
	if (cub->map.line)
		ft_strdel(&cub->map.line);
	if (cub->map.file_2d)
		free_char_2d(cub->map.file_2d);
	if (cub->mlx && cub->img.img)
		mlx_destroy_image(cub->mlx, cub->img.img);
	if (cub->mlx && cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
		free(cub->mlx);
	ft_bzero(cub, sizeof(t_struct));
	exit(EXIT_SUCCESS);
	return (1);
}

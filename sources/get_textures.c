/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:15:03 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:25:40 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** If the get_texture function were not able to obtain the image of each
** textures, then we put inside a buffer all the messages of error
** corresponding. If there is some messages to display, we call exit_faillure
** to start the process of quitting the program with the buffer in parameter.
*/

static void	check_path_text(t_struct *cub)
{
	char str[256];

	str[0] = '\0';
	if (!cub->text.no.img)
		ft_strlcat(str, "Impossible to get the north's texture value\n", 256);
	if (!cub->text.so.img)
		ft_strlcat(str, "Impossible to get the south's texture value\n", 256);
	if (!cub->text.ea.img)
		ft_strlcat(str, "Impossible to get the east's texture value\n", 256);
	if (!cub->text.we.img)
		ft_strlcat(str, "Impossible to get the west's texture value\n", 256);
	if (!cub->text.sp.img)
		ft_strlcat(str, "Impossible to get the sprite's texture value\n", 256);
	if (str[0])
		exit_faillure(cub, str);
}

/*
** This function gets all the informations needed fir each textures.
** We get these informations with the mlx_get_data_adrr function.
*/

static void	get_data_addr(t_texture *text)
{
	text->no.addr = mlx_get_data_addr(text->no.img, &text->no.bpp,
		&text->no.line_length, &text->no.endian);
	text->so.addr = mlx_get_data_addr(text->so.img, &text->so.bpp,
		&text->so.line_length, &text->so.endian);
	text->ea.addr = mlx_get_data_addr(text->ea.img, &text->ea.bpp,
		&text->ea.line_length, &text->ea.endian);
	text->we.addr = mlx_get_data_addr(text->we.img, &text->we.bpp,
		&text->we.line_length, &text->we.endian);
	text->sp.addr = mlx_get_data_addr(text->sp.img, &text->sp.bpp,
		&text->sp.line_length, &text->sp.endian);
}

/*
** This function gets all the texture's images depending on the path
** of each texture. It gets in the same time the size of the textures.
** We put inside a buffer the width and height of each texture.
** Because the calc_size_tile (cub_utils.c) need these informations to
** calculate the right size of tile_size.
** Then we call check_path_text and get_data_adrr (same file).
*/

void		get_texture(t_struct *cub)
{
	cub->text.no.img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_no,
	&cub->text.no.width, &cub->text.no.height);
	cub->text.so.img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_so,
	&cub->text.so.width, &cub->text.so.height);
	cub->text.ea.img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_ea,
	&cub->text.ea.width, &cub->text.ea.height);
	cub->text.we.img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_we,
	&cub->text.we.width, &cub->text.we.height);
	cub->text.sp.img = mlx_xpm_file_to_image(cub->mlx, cub->map.text_sp,
	&cub->text.sp.width, &cub->text.sp.height);
	cub->text.res_text[0] = cub->text.no.width;
	cub->text.res_text[1] = cub->text.no.height;
	cub->text.res_text[2] = cub->text.so.width;
	cub->text.res_text[3] = cub->text.so.height;
	cub->text.res_text[4] = cub->text.ea.width;
	cub->text.res_text[5] = cub->text.ea.height;
	cub->text.res_text[6] = cub->text.we.width;
	cub->text.res_text[7] = cub->text.we.height;
	check_path_text(cub);
	get_data_addr(&cub->text);
}

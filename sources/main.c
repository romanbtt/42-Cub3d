/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:23:48 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:04:37 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function checks if the arguments are valid or not.
** It checks the number of arguments. For this, we need to check three cases.
** The number of arguments. Between two and three.
** The extension of the file. Need to be ".cub".
** And if a third argument is provided, it needs to be "--save".
** Otherwise, we return an error.
*/

static void	check_arguments(t_struct *cub, int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		exit_faillure(cub, "Invalid number of arguments.\n");
	else if (ft_strlen(argv[1]) <= 4 ||
	ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
		exit_faillure(cub, "Invalid file name.\n");
	else if (argc == 3 && ft_memcmp(argv[2], "--save", 6))
		exit_faillure(cub, "Invalid second argument.\n");
}

/*
** This function calculate the size of the window that we need to display.
** It get the size of the screen with the function mlx_get_screen_size.
** And it compares the screen width and screen height with the resolution
** provides in the cub file.
** If the resolution provides in the file is bigger than the screen size.
** Then we assign the screen resolution to the window size.
*/

static void	check_resolution(t_struct *cub)
{
	int screen_width;
	int screen_height;

	mlx_get_screen_size(cub->mlx, &screen_width, &screen_height);
	if (cub->map.width > screen_width)
		cub->map.width = screen_width;
	if (cub->map.height > screen_height)
		cub->map.height = screen_height;
}

/*
** This function initialize the mlx, image, and window.
** If one of them returns 0. It means that the function failed to initialize
** one of the elements. And then we need to return an error.
*/

static void	initialisation_game(t_struct *cub)
{
	if (!(cub->mlx = mlx_init()))
		exit_faillure(cub, "Could't etablish a connection with mlx");
	check_resolution(cub);
	if (!(cub->img.img = mlx_new_image(cub->mlx, cub->map.width,
		cub->map.height)))
		exit_faillure(cub, "Could't create an image with mlx.");
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp,
		&cub->img.line_length, &cub->img.endian);
	if (!(cub->win = mlx_new_window(cub->mlx, cub->map.width, cub->map.height,
		TITLE_WIN)))
		exit_faillure(cub, "Could't create a window with mlx.");
}

/*
** This function set all the elements and memories that we need to the
** calculation during the game.
** We call get_texture to get the textures.
** We calculate the tile_size that we will use.
** We assign some memories to the struct sprites, ray, buff_png.
** We call get_info_sprites to get the sprite.
** We multiply the position of the player by the tile_size.
** We set the rotation speed and walk speed with the definition of
** ROT_SPEED and WALK_SPEED define in cub3d.h
*/

static void	setup_game(t_struct *cub)
{
	get_texture(cub);
	cub->map.tile_size = calc_size_tile(cub);
	if (!(cub->sprites = malloc(sizeof(t_sprites) * cub->map.sp_qty)))
		exit_faillure(cub, "Malloc failled to allocate 'cub->sprites'");
	if (!(cub->ray = malloc(sizeof(t_ray) * cub->map.width)))
		exit_faillure(cub, "Malloc failed to allocate 'cub->ray'");
	if (!(cub->bmp.buff_body = malloc(sizeof(int) *
	cub->map.width * cub->map.height)))
		exit_faillure(cub, "Malloc failed to allocate 'cub->bmp.buff_body'");
	get_info_sprites(cub);
	cub->player.pos.x *= cub->map.tile_size;
	cub->player.pos.y *= cub->map.tile_size;
	cub->player.rot_speed = ROT_SPEED;
	cub->player.walk_speed = WALK_SPEED;
}

/*
** We create a structure cub that we will use along the program.
** We set this struct at 0.
** We call check_arguments (same file).
** We call process_map_file (process_map_file.c).
** We call initialisation_game (same file).
** We call setup_game (same file).
** If the second argument = "--save", then we call save_bmp (save_bmp.c)
** mlx_loop_hook will loop along the game is running calling the function
** update_game (update.game.c).
** We call key_event (key_event.c) to check if a key is pressed along the game.
** We call mlx_loop to start the loop.
*/

int			main(int argc, char **argv)
{
	t_struct cub;

	cub = (t_struct) {0};
	check_arguments(&cub, argc, argv);
	process_map_file(&cub, argv[1]);
	initialisation_game(&cub);
	setup_game(&cub);
	if (argv[2] && !ft_memcmp(argv[2], "--save", 6))
		save_bmp(&cub);
	mlx_loop_hook(cub.mlx, update_game, &cub);
	key_event(&cub);
	mlx_loop(cub.mlx);
}

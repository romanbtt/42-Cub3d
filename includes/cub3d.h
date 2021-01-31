/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:07:06 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 18:15:48 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>

# define PI 3.1415926535f
# define FOV 1.0471975511f
# define WALK_SPEED 50.0f
# define ROT_SPEED 0.1f
# define TITLE_WIN "Cub3D of Robitett - Learning Purpose"

typedef struct		s_pos
{
	float			x;
	float			y;

}					t_pos;

typedef struct		s_sprites
{
	float			dir;
	float			pl_dist;
	int				size;
	int				ofst_x;
	int				ofst_y;
	t_pos			pos;
}					t_sprites;

typedef struct		s_wall
{
	float			perp_dist;
	float			dist_proj_plane;
	float			proj_wall_height;
	int				strp_height;
	int				top_strp;
	int				btm_strp;
	int				ofst_x;
	int				ofst_y;
	float			top_dist;
}					t_wall;

typedef struct		s_helper_ray
{
	t_pos			hit;
	t_pos			intcp;
	t_pos			step;
	t_pos			chk;
	float			dist;
	bool			was_hit;
}					t_helper_ray;

typedef	struct		s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef	struct		s_texture
{
	t_img			sp;
	t_img			no;
	t_img			so;
	t_img			ea;
	t_img			we;
	t_img			curr;
	int				res_text[8];
}					t_texture;

typedef struct		s_map
{
	int				width;
	int				height;
	int				fl_rgb;
	int				ceil_rgb;
	char			*text_no;
	char			*text_so;
	char			*text_we;
	char			*text_ea;
	char			*text_sp;
	char			*map_1d;
	char			**map_2d;
	int				count_id;
	int				col_len;
	int				row_len;
	int				tile_size;
	int				sp_qty;
	char			*line;
	char			*whole_file;
	char			**file_2d;
	int				file_len;
}					t_map;

typedef struct		s_player
{
	int				turn_direction;
	int				walk_fwd_bwd;
	int				walk_rgt_lft;
	float			rot_angle;
	float			rot_speed;
	float			walk_speed;
	t_pos			pos;
}					t_player;

typedef struct		s_ray
{
	t_pos			hit;
	float			ray_angle;
	float			dist;
	bool			hit_vert;
	bool			hit_horz;
	bool			isray_up;
	bool			isray_down;
	bool			isray_left;
	bool			isray_right;
}					t_ray;

typedef struct		s_bmp
{
	unsigned char	buff_header[54];
	int				*buff_body;
}					t_bmp;

typedef struct		s_id
{
	char			**array_no;
	char			**array_so;
	char			**array_ea;
	char			**array_we;
	char			**array_sp;
	char			**array_f;
	char			**array_c;
	char			**array_r;
	int				nb_comma;
}					t_id;

typedef struct		s_struct
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_player		player;
	t_img			img;
	t_ray			*ray;
	t_sprites		*sprites;
	t_texture		text;
	t_bmp			bmp;
	t_id			buff_id;
}					t_struct;

typedef void		(*t_array_func_id)(t_struct *, t_map *, char *);

/*
** cub-utils.c
*/
int					calc_size_tile(t_struct *cub);
float				dist_btw_pts(float x1, float x2, float y1, float y2);
float				normalize_angle(float angle);
bool				is_wall_at(t_map *map, int x, int y);
void				put_in_rgb(char **array, int rgb[3]);

/*
** exit_game.c
*/
void				exit_faillure(t_struct *cub, char *error);
void				free_char_2d(char **ptr);
int					exit_game(t_struct *cub);

/*
** get_info_player.c
*/
void				get_info_player(t_struct *cub, t_player *pl, int row,
						int col);

/*
** get_info_sprites.c
*/
void				get_info_sprites(t_struct *cub);

/*
** get_line_map.c
*/
void				get_line_map(t_struct *cub, char *line);

/*
** get_map_identifier_1.c
*/
void				identifier_n(t_struct *cub, t_map *map, char *line);
void				identifier_so(t_struct *cub, t_map *map, char *line);
void				identifier_e(t_struct *cub, t_map *map, char *line);
void				identifier_w(t_struct *cub, t_map *map, char *line);
void				identifier_s_so(t_struct *cub, t_map *map, char *line);

/*
** get_map_identifier_2.c
*/
void				identifier_f(t_struct *cub, t_map *map, char *line);
void				identifier_c(t_struct *cub, t_map *map, char *line);
void				identifier_r(t_struct *cub, t_map *map, char *line);

/*
** get_next_line.c
*/
int					get_next_line(int fd, char **line);

/*
** get_textures.c
*/
void				get_texture(t_struct *cub);

/*
** is_map_valid.c
*/
void				is_map_valid(t_struct *cub, t_map *map, t_player *pl);

/*
** key_events.c
*/
void				key_event(t_struct *cub);

/*
** main.c
*/
int					main(int argc, char **argv);

/*
** mlx_utils.c
*/
void				insert_pixel(t_img *img, int x, int y, int color);
int					pick_pixel(t_img *img, int x, int y);

/*
** move_player.c
*/
void				move_player(t_map *map, t_player *pl);

/*
** process_map_file_utils.c
*/
bool				is_empty_line(char *line);
bool				is_line_map(char *line);
bool				is_map_identifier(char c);
bool				is_missing_identifier(t_struct *cub, char *line);

/*
** process_map_file.c
*/
void				process_map_file(t_struct *cub, char *file);

/*
** raycasting_horz.c
*/
void				horizontal_casting(t_map *map, t_ray *ray,
						t_helper_ray *horz, t_player *pl);

/*
** raycasting_vert.c
*/
void				vertical_casting(t_map *map, t_ray *ray,
						t_helper_ray *vert, t_player *pl);

/*
** raycasting.c
*/
void				raycasting(t_struct *cub);

/*
** render_projection_1.c
*/
void				render_projection(t_struct *cub);

/*
** render_projection_2.c
*/
void				print_wall(t_struct *cub, t_wall *wall, int col);
void				print_ceiling(t_struct *cub, t_wall *wall, int col);
void				print_floor(t_struct *cub, t_wall *wall, int col);

/*
** render_sprites.c
*/
void				render_sprites(t_struct *cub);

/*
** save_bmp.c
*/
void				save_bmp(t_struct *cub);

/*
** update_game.c
*/
int					update_game(t_struct *cub);
#endif

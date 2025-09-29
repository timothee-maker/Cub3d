/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:58:49 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/29 15:25:42 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __linux__
#  include "mlx.h"
#  include "mlx_int.h"
# endif

# include "get_next_line.h"
# include "libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HEIGHT 800
# define WIDTH 1400

# define PI 3.14159265359
# define W 119
# define A 97
# define S 115
# define D 100
# define EAST 3
# define WEST 2
# define SOUTH 1
# define NORTH 0
# define ECHAP 65307
# define LEFT 65361
# define RIGHT 65363
# define BLOCK 64
# define INT_MAX 2147483647
# define INT_MIN -2147483647
# define SPEED 3
# define ANGLE_SPEED 0.02

# define BONUS 0

# define ERR_MALLOC "AIIIIII le malloc a pete"

typedef struct s_ray
{
	float		corrected_dist;
	float		ray_dir_x;
	float		ray_dir_y;
	float		delta_dx;
	float		delta_dy;
	float		cos_angle;
	float		sin_angle;
	float		pos_x;
	float		pos_y;
	float		dist;
	float		height;
	int			start_y;
	int			end;
	int			side;
	int			color;
	int			index;
	int			map_x;
	int			map_y;
	int			stepx;
	int			stepy;
	int			rev_screen;
	float		side_dx;
	float		side_dy;
}				t_ray;

typedef struct s_pixel
{
	float		wall_x;
	int			face;
	int			tex_x;
	int			tex_y;
	float		step;
	float		tex_pos;
	int			color;
	int			start_y;
	int			end_y;
	int			y;
}				t_pixel;

typedef struct s_index
{
	int			i;
	int			j;
	int			k;
	float		start_x;
}				t_index;

typedef struct s_player
{
	char		dir;
	float		x;
	float		y;
	float		angle;
	bool		k_up;
	bool		k_down;
	bool		k_left;
	bool		k_right;
	bool		r_left;
	bool		r_right;
}				t_player;

typedef struct s_cimg
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_cimg;

typedef struct s_texinfo
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			*floor;
	int			*ceiling;
}				t_texinfo;

typedef struct s_mapinfo
{
	int			fd;
	int			nb_line;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			end_of_map;
	int			start_of_map;
}				t_mapinfo;

typedef struct s_game
{
	t_player	player;
	char		**map;
	void		*mlx;
	void		*win;
	char		**textures;
	t_cimg		img;
	t_cimg		texture[4];
	t_mapinfo	mapinfo;
	t_texinfo	texinfo;
}				t_game;

/*--------------------------PARSING-------------------------------*/
int				parse_args(char *file, t_game *game);
int				parse_data(char *path, t_game *game);
int				fill_tab(t_game *game);
int				get_nb_lines(char *path);
void			draw_map(t_game *parse, t_cimg *image);
char			**get_map(void);
int				open_file(char *file);
int				verify_extension(char *file);
bool			valid_number(char *str);
int				check_rgb(char *rgb);
int				*get_view(char *rgb, int i);
int				fill_view_texture(t_texinfo *texinfo, char *map, int j);
char			*get_texture(char *path_tex, int i);
int				fill_wall_textures(t_texinfo *texinfo, char *map, int j);
int				empty_line(char **map, int j, int i);
int				verify_access(t_texinfo *texture);

/*-------------------------GAME------------------------------------*/
int				draw_loop(t_game *parse);
void			draw_line(t_player *player, t_game *parse, t_index *index,
					t_cimg *image);

/*-----------------------PLAYER----------------------------------*/

void			move_player(t_game *game, t_player *player);
int				key_press(int keycode, t_game *parse);
void			set_player(t_player *player, t_game *game);
int				key_release(int keycode, t_player *player);

/*-------------------------------HOOK-------------------------*/
void			destroy_win(t_game *parse);
int				close_window(t_game *parse);
int				key_hook(int keycode, t_game *parse);

/*-------------------------------FORMULE MATH-------------------*/
bool			touch(float px, float py, t_game *parse);
float			fixed_dist(float delta_x, float delta_y, t_game *parse);
void			draw_square(int x, int y, int size, t_cimg *image);
int				find_face(t_ray *ray);
int				cast_ray(t_game *parse, t_player *player, t_ray *ray);

/*--------------------------MLX TOOLS MODIF------------------------------*/
void			clear_image(t_cimg *img);
int				get_pixel(t_cimg *t, int x, int y);
void			put_pixel(int x, int y, int color, t_cimg *img);

/*-------------------------INIT------------------------------------------*/
void			init_img_clean(t_cimg *img);
void			init_texture_img(t_game *parse, t_cimg *image, char *path);
void			init_img(t_game *parse, t_cimg *image);
void			init_tex(t_pixel *tex, t_ray *ray);
void			init_mlx(t_game *parse);
void			init_ray(t_ray *ray, t_player *player, float start_x, int x);
void			init_mapinfo(t_mapinfo *mapinfo);
void			init_index(t_index *index);
void			init_texinfo(t_texinfo *texinfo);

/*-------------------------SET STRUCT------------------------------------------*/
void			set_texture(t_game *parse, t_ray *ray, t_player *player,
					t_pixel *tex);
void			set_mlx(t_game *parse);

/*---------------------------HANDLE IMAGES-----------------------------------*/
void			load_img(t_game *parse, t_cimg *texture, char *str);
void			get_color_pixel(t_pixel *tex, t_game *parse);

/*--------------------------ERROR-MSG-----------------------------------------*/
int				err_msg(char *str, int code);

/*--------------------------BONUS-------------------------------------------*/
void			minimap(t_game *parse, t_cimg *image, t_player *player);

/*------------------------FREE-SHIT-----------------------------------------*/
void			free_tab(void **tab);
void			free_tex(t_texinfo *texture);
int				ft_atoi_free(const char *str);

#endif
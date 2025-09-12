/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:58:49 by tnolent           #+#    #+#             */
/*   Updated: 2025/09/12 15:54:34 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "mlx_int.h"
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

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_ray
{
	float		corrected_dist;
	float		ray_dir_x;
	float		ray_dir_y;
	float		deltaDistX;
	float		deltaDistY;
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
	int			stepX;
	int			stepY;
	float		sideDistX;
	float		sideDistY;
}				t_ray;

typedef struct s_player
{
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

typedef struct s_parse
{
	t_player	player;
	char		**map;
	void		*mlx;
	void		*win;
	t_cimg		img;
	t_cimg		texture[4];
}				t_parse;

/*-------------------------GAME------------------------------------*/
int	draw_loop(t_parse *parse);
void	draw_line(t_player *player, t_parse *parse, float start_x, int i,
		t_cimg *image);

/*-----------------------PLAYER----------------------------------*/

void			move_player(t_player *player);
int				key_press(int keycode, t_parse *parse);
void			init_player(t_player *player);
int				key_release(int keycode, t_player *player);

/*-------------------------------HOOK-------------------------*/
void			destroy_win(t_parse *parse);
int				close_window(t_parse *parse);
int				key_hook(int keycode, t_parse *parse);

/*-------------------------------FORMULE MATH-------------------*/

bool			touch(float px, float py, t_parse *parse);
float			fixed_dist(float x1, float y1, float x2, float y2,
					t_parse *parse);
float			distance(float x, float y);
void			draw_square(int x, int y, int size, int color, t_cimg *image);
int				find_face(t_ray *ray);
int				cast_ray(t_parse *parse, t_player *player, t_ray *ray);

/*--------------------------PARSING-------------------------------*/
void			draw_map(t_parse *parse, t_cimg *image);
char			**get_map(void);

/*--------------------------MLX TOOLS MODIF------------------------------*/
void			clear_image(t_cimg *img);
int				get_pixel(t_cimg *t, int x, int y);
void			put_pixel(int x, int y, int color, t_cimg *img);

/*-------------------------INIT------------------------------------------*/
void			init_img_clean(t_cimg *img);
void			init_texture_img(t_parse *parse, t_cimg *image, char *path);
void			init_img(t_parse *parse, t_cimg *image);
void			init_tex(t_pixel *tex, t_ray *ray);
void			init_mlx(t_parse *parse);

/*-------------------------SET STRUCT------------------------------------------*/
void			set_texture(t_parse *parse, t_ray *ray, t_player *player,
					t_pixel *tex);
void			set_mlx(t_parse *parse);

/*---------------------------HANDLE IMAGES-----------------------------------*/
void			load_img(t_parse *parse, t_cimg *texture, char *str);

#endif
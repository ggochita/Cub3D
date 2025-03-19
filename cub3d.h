#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include "get_next_line/get_next_line.h"
# include "Libft/libft.h"
# include "minilibx-linux/mlx.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define NUM_KEYS 7
# define KEY_LEFT_IDX	0
# define KEY_RIGHT_IDX	1
# define KEY_W_IDX		2
# define KEY_A_IDX		3
# define KEY_S_IDX		4
# define KEY_D_IDX		5
# define ESC_IDX		6

# define PI 3.14159265

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363


typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_textures_paths
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_textures_paths;

typedef struct s_textures
{
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
}	t_textures;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	angle;
}	t_player;

typedef struct s_game
{
	void				*mlx;
	void				*win_3d;
	t_textures			textures;
	t_textures_paths	textures_paths;
	int					floor_color;
	int					ceiling_color;
	t_map				*map;
	t_player			*player;
	int					keys[NUM_KEYS];
}	t_game;

typedef struct s_dda
{
	float	pos_x;
	float	pos_y;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	sidedist_x;
	float	sidedist_y;
	float	deltadist_x;
	float	deltadist_y;
	int		side;
	int		step_x;
	int		step_y;
}	t_dda;

typedef struct s_draw
{
	int		x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	float	tex_pos;
	float	step;
}	t_draw;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_parse_state
{
	int	textures_done;
	int	colors_done;
	int	map_started;
	int	no_found;
	int	so_found;
	int	we_found;
	int	ea_found;
	int	f_found;
	int	c_found;
}	t_parse_state;

void		err_exit(const char *message, t_map *map);
void		free_map(t_map *map);
void		allocate_map_grid(t_map *map, int height);
void		cleanup_game(t_game *game);
void		update_ns_textures(char *trimmed, t_parse_state *state);
void		update_ew_textures(char *trimmed, t_parse_state *state);
void		update_floor_ceiling(char *trimmed, t_parse_state *state);

void	put_pov_image(t_game *game);


int			count_map_lines(const char *filename);
void		load_map(const char *filename, t_map *map);
void		validate_map(t_map *map);
int			is_map_line(char *line);
int			open_map_file(const char *filename);
int			is_empty_map_line(char *line);
int			is_texture_or_color(char *line);
void		process_map_line(char *line, int *in_map,
int 		*count, int *last_non_empty);
void		check_horizontal_border(t_map *map, int i, int last_char);
void		check_vertical_border(t_map *map, int i, int last_char);
void		check_interior(t_map *map);
void		check_forbidden_chars(t_map *map);

void		check_closed_map(t_map *map);
void		check_player_position(t_map *map);
int			is_valid_char(char c);
int			is_valid_position(t_map *map, int i, int j);
int			is_playable_space(char c);
int			is_space_closed(t_map *map, int i, int j);
void		check_map_alignment(t_map *map);
void		check_borders(t_map *map);

void		parse_elements(const char *filename, t_game *game);
void		check_texture_file(char *path);
int			parse_color(char *line);
int			is_valid_identifier(char *line);
int			is_empty_line(char *line);
void		check_required_elements(t_parse_state *state);
char		*trim_start(char *str);
void		validate_rgb_format(char *str);
char		*clean_path(char *path);
int			init_parse(const char *filename, t_parse_state *state);
void		process_line(char *line, t_parse_state *state, t_game *game);
void		finalize_parse(t_parse_state *state, t_game *game);
void		validate_element_order(char *line, t_parse_state *state);
void		process_identifier(char *line, t_game *game);
void		update_parse_state(char *trimmed, t_parse_state *state);
int			is_valid_path_char(char c);
int			is_valid_rgb_value(char *str);

void		load_textures(t_game *game);
void		load_texture(void *mlx, t_texture *tex, char *path);

void		draw_scene(t_game *game);
void		draw_floor_and_ceiling(t_game *game, t_img *img);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_texture	*select_texture(t_game *game, t_dda *ray);
void		draw_wall_column(t_img *img, t_draw *draw, t_texture *tex);

void		render_frame(t_game *game);
void		draw_wall(t_game *game, t_img *img, t_dda *ray, t_draw *draw);
void		calculate_draw_params(t_draw *draw, float perp_wall_dist);
void		init_ray(t_game *game, t_dda *ray, int x);
void		init_dda_params(t_dda *ray);
int			check_ray_hit(t_game *game, t_dda *ray);
void		perform_dda(t_game *game, t_dda *ray);

int			handle_key(void *param);
int			get_key_index(int key);
int			key_press(int key, void *param);
int			key_release(int key, void *param);
int			close_window(t_game *game);

void		init_player(t_game *game);
void		init_player_direction(t_player *player, char direction);
void		move_player(t_game *game, float dir_x, float dir_y);
void		rotate_player(t_player *player, float angle);
void		set_direction(t_player *player, float dir_x, float dir_y);
void		set_plane(t_player *player, float plane_x, float plane_y);

void		init_game(t_game *game);
int			ft_array_size(char **array);
void		free_split(char **array);
void		check_rgb_values(char **rgb);
void		check_file_extension(char *filename);

#endif

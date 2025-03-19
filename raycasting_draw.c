#include "cub3d.h"

void	calculate_draw_params(t_draw *draw, float perp_wall_dist)
{
	draw->line_height = (int)(WIN_HEIGHT / perp_wall_dist);
	draw->draw_start = -draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line_height / 2 + WIN_HEIGHT / 2;
	if (draw->draw_end >= WIN_HEIGHT)
		draw->draw_end = WIN_HEIGHT - 1;
}

t_texture	*select_texture(t_game *game, t_dda *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->textures.we);
		else
			return (&game->textures.ea);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->textures.so);
		else
			return (&game->textures.no);
	}
}

static void	calculate_tex_coords(t_dda *ray, t_draw *draw, t_texture *tex,
		float perp_wall_dist)
{
	float	wall_x;

	if (ray->side == 0)
		wall_x = ray->pos_y + perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = ray->pos_x + perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	draw->tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		draw->tex_x = tex->width - draw->tex_x - 1;
	draw->step = 1.0 * tex->height / draw->line_height;
	draw->tex_pos = (draw->draw_start - WIN_HEIGHT / 2
			+ draw->line_height / 2) * draw->step;
}

void	draw_wall_column(t_img *img, t_draw *draw, t_texture *tex)
{
	int	y;
	int	tex_y;
	int	color;

	y = draw->draw_start;
	while (y < draw->draw_end)
	{
		tex_y = (int)draw->tex_pos & (tex->height - 1);
		draw->tex_pos += draw->step;
		color = *(int *)(tex->addr + (tex_y * tex->line_length
					+ draw->tex_x * (tex->bits_per_pixel / 8)));
		my_mlx_pixel_put(img, draw->x, y, color);
		y++;
	}
}

void	draw_wall(t_game *game, t_img *img, t_dda *ray, t_draw *draw)
{
	t_texture	*tex;
	float		perp_wall_dist;

	if (ray->side == 0)
		perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	calculate_draw_params(draw, perp_wall_dist);
	tex = select_texture(game, ray);
	calculate_tex_coords(ray, draw, tex, perp_wall_dist);
	draw_wall_column(img, draw, tex);
}

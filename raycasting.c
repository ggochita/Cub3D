#include "cub3d.h"

void	init_ray(t_game *game, t_dda *ray, int x)
{
	float	camera_x;

	camera_x = 2 * x / (float)WIN_WIDTH - 1;
	ray->pos_x = game->player->x;
	ray->pos_y = game->player->y;
	ray->ray_dir_x = game->player->dir_x + game->player->plane_x * camera_x;
	ray->ray_dir_y = game->player->dir_y + game->player->plane_y * camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->deltadist_x = fabs(1 / ray->ray_dir_x);
	ray->deltadist_y = fabs(1 / ray->ray_dir_y);
}

void	init_dda_params(t_dda *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (ray->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->deltadist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (ray->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->deltadist_y;
	}
}

int	check_ray_hit(t_game *game, t_dda *ray)
{
	if (game->map->grid[ray->map_y][ray->map_x] == '1')
		return (1);
	if (ray->map_y < 0 || ray->map_y >= game->map->height
		|| ray->map_x < 0
		|| ray->map_x >= (int)ft_strlen(game->map->grid[ray->map_y]))
		return (2);
	return (0);
}

void	perform_dda(t_game *game, t_dda *ray)
{
	int		hit;
	int		hit_status;

	init_dda_params(ray);
	hit = 0;
	while (!hit)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		hit_status = check_ray_hit(game, ray);
		if (hit_status == 1)
			hit = 1;
		else if (hit_status == 2)
			break ;
	}
}

void	render_frame(t_game *game)
{
	t_img	img;
	t_dda	ray;
	t_draw	draw;
	int		x;

	img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	draw_floor_and_ceiling(game, &img);
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		draw.x = x;
		draw_wall(game, &img, &ray, &draw);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win_3d, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
}

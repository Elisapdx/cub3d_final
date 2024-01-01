/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_drawing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:10:26 by epraduro          #+#    #+#             */
/*   Updated: 2024/01/01 16:42:38 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/cub3d_bonus.h"
#include "../inc/bonus/err_type_bonus.h"

void	draw_floor_sky(t_config **conf, int draw_start, int x)
{
	int	i;
	int	color_c;
	int	color_f;
	int	floor[3];
	int	ceiling[3];

	i = 0;
	fill_colors((*conf)->data->f_color, floor);
	fill_colors((*conf)->data->c_color, ceiling);
	color_f = create_trgb(0, floor[0], floor[1], floor[2]);
	color_c = create_trgb(0, ceiling[0], ceiling[1], ceiling[2]);
	while (i < HEIGHT)
	{
		if (i <= draw_start)
			my_mlx_pixel_put((*conf)->mlx, x, i, color_c);
		else
			my_mlx_pixel_put((*conf)->mlx, x, i, color_f);
		i++;
	}
}

int	find_orientation(t_ray *ray, t_player *p)
{
	if (ray->door_hit == true)
		return (DOOR);
	if (ray->side == true && p->pos_y < ray->map_y)
		return (EAST);
	else if (ray->side == true && p->pos_y > ray->map_y)
		return (WEST);
	else if (ray->side == false && p->pos_x > ray->map_x)
		return (NORTH);
	else if (ray->side == false && p->pos_x < ray->map_x)
		return (SOUTH);
	return (-1);
}

int	draw_walls(t_config **conf, t_ray *ray, int x)
{
	int	dir;

	dir = -1;
	draw_floor_sky(conf, ray->draw_start, x);
	while (ray->draw_start < ray->draw_end)
	{
		ray->tex_y = (int)ray->text_pos & (TEXTURE_H - 1);
		ray->text_pos += ray->step_text;
		dir = find_orientation(ray, (*conf)->usr);
		if (dir == -1)
			return (-1);
		apply_texture(conf, dir, x, ray->draw_start);
		ray->draw_start++;
	}
	return (SUCCESS);
}

int	render_game(t_config **conf, t_ray *ray, t_player *usr)
{
	t_mlx	*mlx;
	int		x;

	x = 0;
	mlx = (*conf)->mlx;
	while (x < WIDTH)
	{
		init_ray_dir(ray, usr, x);
		define_ray_dir(ray, usr);
		start_dda_algo((*conf)->map->sketch, ray);
		get_wall_height(ray);
		find_texture_size(ray, usr);
		if (draw_walls(conf, ray, x) == -1)
			return (-1);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (SUCCESS);
}

int	init_game(t_config **conf)
{
	init_ray_struct(conf);
	load_img(conf);
	if (!(*conf)->ray)
		return (ft_putendl_fd(MALLOC_ERR, STDERR_FILENO));
	if (render_game(conf, (*conf)->ray, (*conf)->usr) < 0)
		return (-1);
	if (load_map(conf, (*conf)->mlx->mlx) != SUCCESS)
		return (ft_putendl_fd(MINMAP_ERR, STDERR_FILENO));
	(*conf)->data->mouse_show = false;
	mlx_loop_hook((*conf)->mlx->mlx, &mouse_move, conf);
	mlx_hook((*conf)->mlx->win, 2, 1L << 0, &key_handler, conf);
	mlx_hook((*conf)->mlx->win, 17, 0, ft_close, conf);
	mlx_loop((*conf)->mlx->mlx);
	return (SUCCESS);
}

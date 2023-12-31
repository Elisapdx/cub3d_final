/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:35:20 by epraduro          #+#    #+#             */
/*   Updated: 2024/01/01 13:36:27 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mandatory/cub3d.h"
#include "../inc/mandatory/err_type.h"

static void	do_move(t_config **conf, double new_x, double new_y)
{
	char		**map;
	t_player	*p;

	map = (*conf)->map->sketch;
	p = (*conf)->usr;
	if (map[(int)(p->pos_x + new_x * (MOVE_SPEED + 0.1))]
		[(int)(p->pos_y)] != '1')
		p->pos_x += new_x * MOVE_SPEED;
	if (map[(int)(p->pos_x)][(int)(p->pos_y + new_y * (MOVE_SPEED + 0.1))]
		!= '1')
		p->pos_y += new_y * MOVE_SPEED;
}

void	move_keys(t_config **conf, int key_pressed)
{
	t_player	*p;

	p = (*conf)->usr;
	if (key_pressed == W_KEY)
		do_move(conf, p->dir_x, p->dir_y);
	else if (key_pressed == S_KEY)
		do_move(conf, -p->dir_x, -p->dir_y);
	else if (key_pressed == A_KEY)
		do_move(conf, -p->dir_y, p->dir_x);
	else if (key_pressed == D_KEY)
		do_move(conf, p->dir_y, -p->dir_x);
}

void	rotate_keys(t_config **conf, int key_pressed)
{
	t_player	*p;

	p = (*conf)->usr;
	if (key_pressed == RIGHT_KEY)
	{
		p->old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = p->old_dir_x * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
		p->old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y
			* sin(-ROT_SPEED);
		p->plane_y = p->old_plane_x * sin(-ROT_SPEED) + p->plane_y
			* cos(-ROT_SPEED);
	}
	else if (key_pressed == LEFT_KEY)
	{
		p->old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = p->old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		p->old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = p->old_plane_x * sin(ROT_SPEED) + p->plane_y
			* cos(ROT_SPEED);
	}
}

void	reload_img(t_config **conf)
{
	mlx_destroy_image((*conf)->mlx->mlx, (*conf)->mlx->img);
	(*conf)->mlx->img = mlx_new_image((*conf)->mlx->mlx, WIDTH, HEIGHT);
	if (!(*conf)->mlx->img)
		return ;
	(*conf)->mlx->addr = mlx_get_data_addr((*conf)->mlx->img, \
		&(*conf)->mlx->bpp, &(*conf)->mlx->line_len, &(*conf)->mlx->endian);
	if (!(*conf)->mlx->addr)
		return ;
	render_game(conf, (*conf)->ray, (*conf)->usr);
}

int	key_handler(int key_pressed, t_config **conf)
{
	if (key_pressed == ESC_KEY)
		ft_close(conf);
	move_keys(conf, key_pressed);
	rotate_keys(conf, key_pressed);
	reload_img(conf);
	if (!(*conf)->mlx->img || !(*conf)->mlx->addr)
		return (-1);
	return (SUCCESS);
}

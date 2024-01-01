/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:36:33 by epraduro          #+#    #+#             */
/*   Updated: 2024/01/01 14:03:22 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/cub3d_bonus.h"
#include "../inc/bonus/err_type_bonus.h"

int	mouse_move(t_config **conf)
{
	int	x;
	int	y;

	if ((*conf)->data->mouse_show == true)
	{
		mlx_mouse_show();
		return (0);
	}
	mlx_mouse_hide();
	mlx_mouse_get_pos((*conf)->mlx->win, &x, &y);
	if (x < WIDTH / 2)
		rotate_keys(conf, LEFT_KEY);
	else if (x > WIDTH / 2)
		rotate_keys(conf, RIGHT_KEY);
	mlx_mouse_move((*conf)->mlx->win, WIDTH / 2, HEIGHT / 2);
	render_game(conf, (*conf)->ray, (*conf)->usr);
	load_map(conf, (*conf)->mlx->mlx);
	return (1);
}

void	handle_door(t_config **conf)
{
	int			i;
	int			j;
	t_player	*p;

	i = -1;
	p = (*conf)->usr;
	while ((*conf)->map->sketch[++i])
	{
		j = -1;
		while ((*conf)->map->sketch[i][++j])
		{
			if ((*conf)->map->sketch[i][j] == '2')
			{
				if ((int)p->pos_x == i && (int)p->pos_y == j)
					return ;
				(*conf)->map->sketch[i][j] = '3';
			}
			else if ((*conf)->map->sketch[i][j] == '3')
			{
				if ((int)p->pos_x == i && (int)p->pos_y == j)
					return ;
				(*conf)->map->sketch[i][j] = '2';
			}
		}
	}
}

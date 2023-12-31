/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_dup_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:08:07 by epraduro          #+#    #+#             */
/*   Updated: 2024/01/01 14:08:08 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/cub3d_bonus.h"
#include "../inc/bonus/err_type_bonus.h"

static void	examine_path(t_map *map, char **tmp, t_pos pos, char *to_fill)
{
	if (pos.y < 0 || pos.x < 0 \
		|| pos.y >= map->map_len + 2 \
		|| !ft_strchr(to_fill, tmp[pos.y][pos.x]) \
		|| tmp[pos.y][pos.x] == '1' || map->anomaly)
		return ;
	if (tmp[pos.y][pos.x] && tmp[pos.y][pos.x] == '/')
		map->anomaly = true;
	tmp[pos.y][pos.x] = 'X';
	examine_path(map, tmp, (t_pos){pos.x - 1, pos.y}, to_fill);
	examine_path(map, tmp, (t_pos){pos.x + 1, pos.y}, to_fill);
	examine_path(map, tmp, (t_pos){pos.x, pos.y - 1}, to_fill);
	examine_path(map, tmp, (t_pos){pos.x, pos.y + 1}, to_fill);
}

bool	flood_fill(t_map *map, char **tmp)
{
	int		i;
	t_pos	pos;

	i = -1;
	map->anomaly = false;
	while (tmp[++i])
	{
		while (tmp[i] && ft_strchr(tmp[i], '0'))
		{
			pos = find_pos('0', tmp);
			if (pos.x < 0 || pos.y < 0)
				return (false);
			examine_path(map, tmp, pos, "02/NWSE");
		}
		if (map->anomaly == true)
			return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:55:49 by epraduro          #+#    #+#             */
/*   Updated: 2024/01/01 16:31:58 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/cub3d_bonus.h"
#include "../inc/bonus/err_type_bonus.h"

/*
* CheckList for the Map: kquetat-
TODO check extension .cub ✅
TODO collect map, trim \n ✅
TODO Check map characters 😊
TODO At the same time check at least for ONLY one player, Not more than one. 😊
TODO Surround (entouré la carte) map with '/' ou pas... juste les espaces.
TODO Check map is closed using flood fill
! Need to check if there is more to add...

* CheckList for the Data ABOVE the map: epraduro
TODO collect data, STOP condition is: if we encouter map we stop parsing.
TODO check if all data is present.
TODO check if path of texture is valid.
TODO check format of data SO, WE, NO, EA, C, F.
TODO color: check that colors are separated by colons ",".
TODO color: check that integer doesn't exceed 0 - 255.
*/

int	main(int ac, char **av)
{
	int			err_type;
	t_config	*conf;

	if (ac < 2 || check_extension(av[1]) < 0)
		return (-1);
	err_type = parse_data(&conf, av);
	if (err_type == MAP_ERR)
		return (ft_putendl_fd(GET_SKETCH_ERR, STDERR_FILENO));
	else if (err_type == DATA_ERR)
		return (ft_putendl_fd(GET_DATA_ERR, STDERR_FILENO));
	if (initialize_mlx_win(&conf) < 0 || stock_image(&conf) < 0)
		return (free_table_err(&conf, NULL, -1));
	if (init_cub(&conf) < 0)
		return (free_table_err(&conf, NULL, -1));
	init_game(&conf);
	return (SUCCESS);
}

#include "inc_bonus/cub3d_bonus.h"
#include "inc_bonus/parse_err_bonus.h"

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

	if (ac < 2)
		return (ft_putendl_fd(ARG_ERR, STDERR_FILENO));
	err_type = parse_data(&conf, av);
	if (err_type == FAILS)
		return (-1);
	else if (err_type == 2)
		return (2);
	if (init_cub(&conf) == -1)
		return (-1);
	else if (init_game(&conf) == -1)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:56:55 by elel-bah          #+#    #+#             */
/*   Updated: 2025/01/16 19:03:20 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_valid_rt_file(int ac, char **av)
{
	int	i;
	int	fd;

	fd = 0;
	if (ac != 2 || !av[1])
		return (1);
	i = ft_strlen(av[1]);
	if (i < 4)
		return (1);
	if (i > 3 && ft_strncmp(av[1] + i - 3, ".rt", 3) != 0)
	{
		// fd = open(av[1], O_RDONLY);
		// if (fd < 0)
			return (1);
		// close(fd);
	}
	// else
	// 	return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_scene	*scene;
	int		fd;

	if (is_valid_rt_file(ac, av))
		report_error("wrong args : Please try enter filename.rt");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		report_error("wrong args : Please try enter filename.rt");
	scene = allocate_scene();
	if (!scene)
		(close(fd), report_error("allocation"));
	parse_scene_file(scene, fd);
	ft_render(scene);
	gc_cleanup(&garbage_collector, garbage_collector);
	close(fd);
	return (0);
}


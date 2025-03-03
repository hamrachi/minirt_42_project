/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:56:55 by elel-bah          #+#    #+#             */
/*   Updated: 2025/03/01 19:24:30 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	is_valid_rt_file_b(int ac, char **av)
{
	int	i;
	int	fd;

	fd = 0;
	if (ac != 2 || !av[1])
		return (1);
	i = ft_strlen_b(av[1]);
	if (i < 4)
		return (1);
	if (i > 3 && ft_strncmp_b(av[1] + i - 3, ".rt", 3) != 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_world	*scene;
	int		fd;

	if (is_valid_rt_file_b(ac, av))
		report_error_b("wrong args : Please try enter filename.rt");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	scene = allocate_scene_b();
	if (!scene)
		report_error_b("allocation");
	parse_scene_file_b(scene, fd);
	ft_render_b(scene);
	gc_cleanup_b(&g_garbage_collector, g_garbage_collector);
	close(fd);
	return (0);
}

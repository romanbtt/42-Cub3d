/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:21:35 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 16:56:09 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function reallocates some memories each time the function is called.
** We put inside a buffer (map_1d), the line passed in argument.
** Each time, the function is called, we add this line in the buffer.
*/

static void	realloc_line(t_struct *cub, char *line)
{
	char	*tmp;
	char	*tmp_2;

	tmp = ft_strdup(cub->map.map_1d);
	free(cub->map.map_1d);
	tmp_2 = ft_strjoin(line, "\n");
	cub->map.map_1d = ft_strjoin(tmp, tmp_2);
	free(tmp);
	free(tmp_2);
}

/*
** This function checks if the line doesn't contains a forbidden char.
** If yes, we return an error.
** Then we put inside a buffer (map_1d), the line passed in argument.
** If it is the first line, we call ft_strjoin to put an '\n' at the end of
** the line.
** If it is not the first line, we call realloc_line to reallocate some
** memories and put all the lines separate by '\n' inside the same buffer.
*/

void		get_line_map(t_struct *cub, char *line)
{
	int		i;

	i = 1;
	cub->map.row_len++;
	while (line[i - 1] != '\n' && line[i - 1] != '\0')
	{
		if (!ft_strchr("012 NSEW", line[i]))
		{
			ft_strdel(&line);
			exit_faillure(cub, "Invalid element in the map\n");
		}
		i++;
	}
	if (cub->map.row_len == 1)
		cub->map.map_1d = ft_strjoin(line, "\n");
	else
		realloc_line(cub, line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romanbtt <marvin@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:26:47 by romanbtt          #+#    #+#             */
/*   Updated: 2021/01/30 17:24:43 by romanbtt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define STR_ID_MAJ "NSWERFC"
#define STR_ID_MIN "nswerfc"

/*
** This function choose which function we need to choose depending on which
** identifier was passed in parameter.
** For this we use an array of pointer of function. We declared all the function
** in this array. To choose the right function to call, we use a loop until
** the identifier passed in parameter is different than STR_ID_MAJ
** or STR_ID_MIN. For each loop, we increment a counter i.
** When it stops, we found our index of the right function. Then we call the
** right function with the index of the array of pointer of function.
*/

static void		get_map_identifier(t_struct *cub, char *line)
{
	int						i;
	static t_array_func_id	func_id[7] = {identifier_n, identifier_s_so,
		identifier_w, identifier_e, identifier_r, identifier_f, identifier_c};

	i = 0;
	while (line[0] != STR_ID_MAJ[i] && line[0] != STR_ID_MIN[i])
		i++;
	(*func_id[i])(cub, &cub->map, line);
	cub->map.count_id++;
}

/*
** This function checks if the map file is valid or not.
** For each line, we check if it is an empty line (is_empty_line).
** If yes, we continue with the next loop.
** We check if the first char of the line is an identifier.
** If yes, we call get_map_identifier.
** We check if the line contains the description of the map.
** IF yes, we call get_line_map.
** Otherwise, we quit the program with an error.
** When the loop reaches his end, we call is_map_valid to verify the map.
*/

static void		is_file_valid(t_struct *cub, char **file)
{
	int i;

	i = 0;
	while (file[i])
	{
		if (is_empty_line(file[i]) == true)
			continue;
		else if (is_map_identifier(file[i][0]) == true && cub->map.count_id < 8)
			get_map_identifier(cub, file[i]);
		else if (is_line_map(file[i]) && !is_missing_identifier(cub, file[i]))
			get_line_map(cub, file[i]);
		else
			exit_faillure(cub, "The map is not valid.\n");
		i++;
	}
	is_map_valid(cub, &cub->map, &cub->player);
}

/*
** This function puts inside an array, a line returned by get_nex_line.
** If it is the first time, we put this line inside whole_file.
** If it is not the first time, we reallocate some memories to store all the
** lines inside this same buffer whole_file.
** If ret (the return of get_next_line) is equal to zero.
** Then we split by '\n' the whole_file and put it inside a 2d array file_2d.
*/

static void		put_in_buffer(t_struct *cub, char *line, int ret)
{
	char *tmp;
	char *tmp_2;

	cub->map.file_len++;
	if (cub->map.file_len == 1)
		cub->map.whole_file = ft_strjoin(line, "\n");
	else
	{
		tmp = ft_strdup(cub->map.whole_file);
		ft_strdel(&cub->map.whole_file);
		tmp_2 = ft_strjoin(line, "\n");
		cub->map.whole_file = ft_strjoin(tmp, tmp_2);
		ft_strdel(&tmp);
		ft_strdel(&tmp_2);
	}
	if (ret == 0)
	{
		cub->map.file_2d = ft_split(cub->map.whole_file, '\n');
		ft_strdel(&cub->map.whole_file);
	}
}

/*
** This function read the file line by line and return it.
** We start to open the file, if it fails, we return an error.
** Then until ret is not equal to 0, we call get_next_line to obtain all
** the lines. Right after we get a line, we call put_in_buffer.
** When we are outside of the loop, we call is_file_valid to check if the file
** is valid or not.
*/

void			process_map_file(t_struct *cub, char *file)
{
	int ret;
	int fd;

	ret = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		exit_faillure(cub, "Could't open the map file.\n");
	while (ret != 0)
	{
		ret = get_next_line(fd, &cub->map.line);
		put_in_buffer(cub, cub->map.line, ret);
		ft_strdel(&cub->map.line);
	}
	close(fd);
	is_file_valid(cub, cub->map.file_2d);
}

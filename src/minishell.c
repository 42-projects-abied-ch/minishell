/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:00:40 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 12:08:41 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	store_paths(t_path **paths, char *path)
{
	t_path	*new;

	new = pathnew(path);
	if (!new)
		return (free_paths(paths), -1);
	pathadd_back(paths, new);
	return (0);
}

int	get_paths(t_shell *data, t_path **paths)
{
	char	**temp;
	char	**path_array;
	int		i;

	i = -1;
	path_array = data->environment;
	while (*++path_array)
	{
		if (ft_strnstr(*path_array, "PATH", 4))
		{
			*path_array += 5;
			temp = ft_split(*path_array, ':');
			if (!temp)
				return (-1);
			while (temp[++i])
			{
				if (store_paths(paths, temp[i]) == -1)
					return (-1);
			}
			free(temp);
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	data;
	t_path	**paths;

	data.environment = env;
	paths = (t_path **)malloc(sizeof(t_path));
	if (!paths)
		return (-1);
	*paths = NULL;
	get_paths(&data, paths);
	read_input(&data);
	if (argc || argv)
		return (0);
	return (0);
}

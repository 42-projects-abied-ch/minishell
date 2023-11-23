/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:32:48 by sstanfel          #+#    #+#             */
/*   Updated: 2023/11/19 17:40:01 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function checks if a given string contains any of the characters 
 * '-', '*', or '/'.
 * 
 * @return 1 if the string "arg" contains any of the characters '-', '*', 
 * or '/', and 0 otherwise.
 */
static int	issign(char *arg)
{
	if (ft_strchr(arg, '-') != NULL)
		return (1);
	else if (ft_strchr(arg, '*') != NULL)
		return (1);
	else if (ft_strchr(arg, '/') != NULL)
		return (1);
	return (0);
}

/*
 * The function checks if a given argument is a valid identifier
 *  for exporting in C programming language.
 * 
 * @param arg The parameter `arg` is a pointer to a character array (string).
 * 
 * @return The function `export_error` returns different values based on 
 * certain conditions
 */
int	export_error(char *arg, int argname)
{
	if ((ft_strchr(arg, '=') != NULL) && arg[2] == '\0')
		return (ft_putendl_fd(" not a valid identifier", 2), 1);
	else if (ft_strnstr(arg, "-=", ft_strlen(arg)) != 0)
		return (ft_putendl_fd(" not a valid identifier", 2), 1);
	else if (ft_strchr(arg, '=') == NULL)
	{
		if (issign(arg) != 0 && argname)
			return (ft_putendl_fd(" not a valid identifier", 2), 1);
		if ((ft_isdigit(arg[0])) && argname)
			return (ft_putendl_fd(" not a valid identifier", 2), 1);
		return (2);
	}
	return (0);
}

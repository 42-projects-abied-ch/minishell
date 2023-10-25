/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:08:07 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/25 21:54:11 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*replace(char *str, t_shell *data)
// {
// 	char	*arg;

// 	arg = ft_strndup("Hello", 6);
// 	if (!arg)
// 		return (NULL);
// 	if (data)
// 	{
// 		if (ft_strncmp(str, "$arg", 4) == 0)
// 			return (free(str), arg);
// 	}
// 	return (NULL);
// }

char	*replace(char *str, t_shell *data)
{
	char	**env;
	char	*ret;

	env = data->environment;
	str++;
	while (*env)
	{
		if (ft_strncmp(str, *env, ft_strlen(str)) == 0)
		{
			ret = ft_strdup(*env + (ft_strlen(str) + 1));
			if (!ret)
				return (NULL);
			return (free(--str), ret);
		}
		env++;
	}
	return (NULL);
}

int	expand_sequences(t_shell *data)
{
	t_quotes	*head;

	head = *data->sequences;
	while (head)
	{
		if (head->status == IN_DOUBLE_QUOTES)
		{
			head->sequence = expand_dquotes(head->sequence, data);
			if (!head->sequence)
				return (-1);
		}
		else if (head->status == UNQUOTED)
		{
			head->sequence = expand_uquotes(head->sequence, data);
			if (!head->sequence)
				return (-1);
		}
		head = head->next;
	}
	return (0);
}

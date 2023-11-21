/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:57:06 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/21 16:13:29 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_op	*get_next_token(t_op **head)
{
	char	*temp;
	char	*merged_args;
	t_op	*new;

	merged_args = NULL;
	if (*head && (*head)->status == PUT_SPACE_HERE)
		*head = (*head)->next;
	while ((*head) && (*head)->status != PUT_SPACE_HERE)
	{
		temp = merged_args;
		if (!merged_args)
			merged_args = ft_strdup((*head)->sequence);
		else
			merged_args = ft_strjoin(merged_args, (*head)->sequence);
		if (!merged_args)
			return (NULL);
		free(temp);
		if (*head && (*head)->s_char)
		{
			new = opnew(NULL, 0, (*head)->s_char, 0);
			*head = (*head)->next;
			return (new);
		}
		*head = (*head)->next;
		if (!(*head) || (*head)->status == PUT_SPACE_HERE)
		{
			new = opnew(merged_args, 0, 0, ft_strlen(merged_args));
			return (free(merged_args), new);
		}
	}
	return (NULL);
}

int	merge_args(t_shell *data)
{
	t_op	**new_list;
	t_op	*new;
	t_op	*head;
	
	new_list = malloc(sizeof(t_op));
	if (!new_list)
		return (-1);
	*new_list = NULL;
	head = *data->operators;
	while (head)
	{
		new = get_next_token(&head);
		if (!new)
			break ;
		opadd_back(new_list, new);
	}
	free_opps(data->operators);
	data->operators = new_list;
	return (0);
}


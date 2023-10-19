/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:26:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/19 19:56:02 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_path	*pathnew(char *content)
{
	t_path	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->path = content;
	new->next = NULL;
	return (new);
}

void	pathadd_back(t_path **lst, t_path *new)
{
	t_path	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	free_paths(t_path **stack_a)
{
	t_path	*temp;
	t_path	*current;

	current = *stack_a;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
}
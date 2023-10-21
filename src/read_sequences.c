/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sequences.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:41:15 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/21 23:10:02 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *replace(char *current, size_t *i)
{
    char *temp;
    char *new;
    char *expanded_content;
	
	expanded_content = "EXPANSION CONTENT";
    size_t index;
	index = *i;
    temp = ft_strndup(current, index);
    if (!temp)
        return NULL;
    while (current[index] && !myisspace(current[index]))
        index++;
    *i = index;
    new = ft_strjoin(temp, expanded_content);
    if (!new)
		return (free(temp), NULL);
	free(temp);
    return new;
}

char *expand_dquotes(t_quotes *current)
{
    size_t i = 0;
    char *new;
    char *temp;

	new = NULL;
    while (current->sequence[i])
    {
        if (current->sequence[i] == '$')
        {
            temp = replace(current->sequence, &i);
            if (!temp)
                return NULL;
            if (!new)
                new = temp;
            else
            {
                char *old_new = new;
                new = ft_strjoin(old_new, temp);
				if (!new)
					return (free(old_new), free(temp), NULL);
				printf("new after joining: %s\n i : %zu\n", new, i);

                free(old_new);
                free(temp);
            }
        }
        else
            i++;
    }
    if (!new)
        return ft_strdup(current->sequence);
    free(current->sequence);
    return new;
}


void	expand_sequences(t_shell *data)
{
	t_quotes	*head;

	head = *data->sequences;
	while (head)
	{
		if (head->status == IN_DOUBLE_QUOTES)
			head->sequence = expand_dquotes(head);
		printf("%s\n", head->sequence);
		head = head->next;
	}
}

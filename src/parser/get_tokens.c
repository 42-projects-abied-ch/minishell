/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:11:38 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/21 23:19:15 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	skip_whitespaces(t_shell *data, size_t *j, int *quote_status,
size_t *words)
{
	int	prev_status;

	prev_status = 0;
	while (data->raw_input[*j] && myisspace(data->raw_input[*j]))
	{
		if (*j > 0)
			isquote(data->raw_input[*j - 1], &prev_status);
		else
			prev_status = *quote_status;
		isquote(data->raw_input[*j], quote_status);
		if ((quote_status == UNQUOTED || (prev_status != *quote_status))
			&& (myisspace(data->raw_input[*j]) || !data->raw_input[*j]))
			*words += 1;
		*j += 1;
	}
}

static char	**fill_token_array(t_shell *d, size_t words)
{
	if (init_vars(d, words) == -1)
		return (NULL);
	while (++d->tok.i < words)
	{
		d->tok.k = d->tok.j;
		while (d->tok.j < ft_strlen(d->raw_input))
		{
			isquote(d->raw_input[d->tok.j], &d->tok.st);
			if ((d->tok.st == UNQUOTED && myisspace(d->raw_input[d->tok.j]))
				|| !d->raw_input[d->tok.j + 1])
			{
				d->tok.j++;
				if (!d->raw_input[d->tok.j])
					d->tok.j++;
				d->tok.tokens[d->tok.i] = ft_strndup(&d->raw_input[d->tok.k],
						d->tok.j - d->tok.k - 1);
				break ;
			}
			d->tok.j++;
		}
		if (d->tok.j < ft_strlen(d->raw_input))
			skip_whitespaces(d, &d->tok.j, &d->tok.st, NULL);
	}
	d->tok.tokens[d->tok.i] = NULL;
	return (d->tok.tokens);
}

char	**get_token_array(t_shell *data, size_t i)
{
	int		quote_status;
	int		prev_status;
	size_t	words;
	char	**token_array;

	words = 0;
	quote_status = 0;
	while (data->raw_input[++i])
	{
		prev_status = quote_status;
		isquote(data->raw_input[i], &quote_status);
		if ((quote_status == UNQUOTED || prev_status != quote_status)
			&& (myisspace(data->raw_input[i])))
			words++;
		if (data->raw_input[i] && myisspace(data->raw_input[i]))
			skip_whitespaces(data, &i, &quote_status, &words);
	}
	words++;
	token_array = NULL;
	token_array = fill_token_array(data, words);
	if (!token_array)
		return (NULL);
	return (token_array);
}

int	add_tokens_to_list(char **args, t_shell *data, int quote_status, size_t i)
{
	size_t		j;
	char		*temp;

	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			temp = &args[i][j];
			isquote(args[i][j], &quote_status);
			if (quote_status == IN_DOUBLE_QUOTES)
				j += dquotes(temp + 1, data);
			else if (quote_status == IN_SINGLE_QUOTES)
				j += squotes(temp + 1, data);
			else
				j += uquote(temp, data);
		}
		if (args[i] && args[i + 1])
		{
			if (quoteadd_back(data->sequences,
					quotenew(NULL, PUT_SPACE_HERE, 0)) == -1)
				return (-1);
		}
	}
	return (0);
}

int	tokenize(t_shell *data)
{
	char		**args;
	int			quote_status;

	quote_status = 0;
	if (check_quotes(data) == -1)
		return (-1);
	args = get_token_array(data, -1);
	if (!args)
		return (-1);
	if (add_tokens_to_list(args, data, quote_status, -1) == -1)
		return (-1);
	free_array(args);
	return (0);
}
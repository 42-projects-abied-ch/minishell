/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:54:18 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/20 15:41:02 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

typedef struct s_path
{
	char				*path;
	struct s_path		*next;
}	t_path;

typedef struct s_quotes
{
	char				*sequence;
	int					status;
	struct s_quotes		*next;
}	t_quotes;

#endif
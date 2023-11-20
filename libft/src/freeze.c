/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeze.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 21:21:54 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/20 21:22:35 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	freeze(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

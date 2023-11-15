/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:52:03 by abied-ch          #+#    #+#             */
/*   Updated: 2023/11/09 14:01:58 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * The function redirects the input of a shell to a specified file descriptor.
 
 * @param input_fd The `input_fd` parameter is the file descriptor of the input
 * file that we want to redirect to the standard input (stdin) of the shell.
 */
int	redirect_input(t_shell *data, int input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		return (perror("output redirection failed"), -1);
	return (data->exit);
}

/**
 * The function redirects the output of a shell command to a specified file 
 * descriptor.
 *
 * @param output_fd The `output_fd` parameter is the file descriptor that 
 * represents the output file or
 * device where the standard output should be redirected to.
 * 
 * @return the value of `data->exit`.
 */
int	redirect_output(t_shell *data, int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		return (perror("output redirection failed"), -1);
	return (data->exit);
}

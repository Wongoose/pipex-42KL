/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:04:10 by zwong             #+#    #+#             */
/*   Updated: 2022/09/22 11:33:06 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// perror is a built-in function to return error in the terminal
// STDERR = 2
void	err_exit(char *err)
{
	perror(err);
	exit(1);
}

// I putstr into fd 2 cause that is STDERR!
void	invalid_argc(int argc)
{
	if (argc < 5)
		ft_putstr_fd("ERROR: Too few arguments\n", 2);
	else if (argc > 5)
		ft_putstr_fd("ERROR: Too many arguments\n", 2);
	exit(1);
}

// End of the body function, when program fails to find a cmd_path,
// then free all
void	free_all_paths(char **split_paths)
{
	int	i;

	i = 0;
	while (split_paths[i])
		free(split_paths[i++]);
	free(split_paths);
}

// Extra function to close all existing files
void	close_all_fd(struct s_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	close(pipex->fd_infile);
	close(pipex->fd_outfile);
}

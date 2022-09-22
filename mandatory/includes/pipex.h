/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:03:30 by zwong             #+#    #+#             */
/*   Updated: 2022/09/22 11:35:11 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../../libft/libft.h"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd_infile;
	int		fd_outfile;
	int		pipe[2];
	char	**cmd_args;

}	t_pipex;

void	execute_cmd(struct s_pipex *pipex, char **envp);
void	err_exit(char *err);
void	close_all_fd(struct s_pipex *pipex);
void	free_all_paths(char **split_paths);
void	invalid_argc(int argc);

#endif
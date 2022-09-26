/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:05:40 by zwong             #+#    #+#             */
/*   Updated: 2022/09/22 11:30:09 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// This is a forked child
// dup2: Copy old fd and create a new fd (both have the same read pointer)
// cmd_args: Project takes 2 commands in total.
// So, child 1 only splits the arguments of the 1st command
// cmd_args is needed later when executing shell command
void	init_child_one(struct s_pipex *pipex, char **argv, char **envp)
{
	dup2(pipex->pipe[1], STDOUT_FILENO);
	close(pipex->pipe[0]);
	dup2(pipex->fd_infile, STDIN_FILENO);
	pipex->cmd_args = ft_split(argv[2], ' ');
	execute_cmd(pipex, envp);
}

// Same logic as Child 1
void	init_child_two(struct s_pipex *pipex, char **argv, char **envp)
{
	dup2(pipex->pipe[0], 0);
	close(pipex->pipe[1]);
	dup2(pipex->fd_outfile, 1);
	pipex->cmd_args = ft_split(argv[3], ' ');
	execute_cmd(pipex, envp);
}

/* 
	FROM ntan-wan
	1. open(..., 0644)
	-  "0644" is the permission bit.
	-  The first digit '0' in "0644" selects the set user ID on execution (4) 
	   and set group ID on execution (2) and sticky (1) attributes.
	   When an executable file's setuid permission is set, users may execute 
	   that program with a level of access that matches the user who owns the 
	   file.
	Example :
	(ugs = set user ID, set group ID, sticky)
	decimal ->		"0"		"6"		 "4"	 "4"
	binary  ->		"000"	"110"	"100"	"100"
	permission ->	"ugs"	"rwx"	"rwx"	"rwx"
	who ->					user	group	others
 */

void	init_pipex(struct s_pipex *pipex, int argc, char **argv)
{
	pipex->fd_infile = open(argv[1], O_RDONLY);
	if (pipex->fd_infile < 0)
		err_exit("Failed to open infile");
	pipex->fd_outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->fd_outfile < 0)
		err_exit("Failed to open outfile");
	if (pipe(pipex->pipe) < 0)
		err_exit("Failed to execute pipe() command");
}

// First, check for invalid argument count
// init_pipex: Initialize pipex infile, outfile, and pipe
// get_split_paths: Search through all possible command paths
// fork(): Split processes into child and parent (TWICE)
// close all files when done
// waitpid: wait in order of children response (when child is done)
int	main(int argc, char **argv, char **envp)
{
	struct s_pipex	pipex;

	if (argc != 5)
		invalid_argc(argc);
	init_pipex(&pipex, argc, argv);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		err_exit("Failed to 1st fork()");
	if (pipex.pid1 == 0)
		init_child_one(&pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		err_exit("Failed to 2nd fork()");
	if (pipex.pid2 == 0)
		init_child_two(&pipex, argv, envp);
	close_all_fd(&pipex);
	waitpid(pipex.pid1, 0, 0);
	waitpid(pipex.pid2, 0, 0);
	return (0);
}

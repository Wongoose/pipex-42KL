#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../../libft/libft.h"

typedef	struct s_pipex
{
    pid_t	pid1;
    pid_t	pid2;
	pid_t	res;
	int		status;
	int		fd_infile;
	int		fd_outfile;
	int		pipe[2];
	char	**cmd_args;

}   t_pipex;

char	*get_cmd_path(char *cmd, char **envp);
void	init_child_one(struct s_pipex *pipex, char **argv, char **envp);
void	init_child_two(struct s_pipex *pipex, char **argv, char **envp);

#endif
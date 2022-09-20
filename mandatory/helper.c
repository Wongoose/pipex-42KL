#include "includes/pipex.h"

// convert this to a common child main function
// create 2 fork for both children
void	execute_cmd(struct s_pipex *pipex, char **envp)
{
	char	*cmd;
	char	*cmd_path;

	cmd = pipex->cmd_args[0];
	cmd_path = get_cmd_path(cmd, envp);
	if (!cmd_path)
	{
		printf("ERROR: No command path found!");
	}
    printf("\n=EXECUTE CMD: %s %s\n", pipex->cmd_args[0], pipex->cmd_args[1]);
	execve(cmd_path, pipex->cmd_args, envp);
}

void    init_child_one(struct s_pipex *pipex, char **argv, char **envp)
{
    printf("\nINIT CHILD ONE\n");
    dup2(pipex->pipe[1], STDOUT_FILENO);
    printf("\nCHILD ONE: dup2 pipe[1]\n");
    close(pipex->pipe[0]);
    printf("\nCHILD ONE: close pipe[0]\n");
    dup2(pipex->fd_infile, STDIN_FILENO);
    printf("\nCHILD ONE: dup2 fd_infile\n");
    pipex->cmd_args = ft_split(argv[2], ' ');
    // exec cmd
    execute_cmd(pipex, envp);
}

void    init_child_two(struct s_pipex *pipex, char **argv, char **envp)
{
    printf("\nINIT CHILD TWO\n");
    dup2(pipex->pipe[0], 0);
    close(pipex->pipe[1]);
    dup2(pipex->fd_outfile, 1);
    pipex->cmd_args = ft_split(argv[3], ' ');
    // exec cmd
    execute_cmd(pipex, envp);
}
#include "includes/pipex.h"

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

// Appends cmd string to each path to check whether it is valid,
// If has a valid path, returns final valid "cmd_path".
char	*check_cmd_path(char **split_paths, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (split_paths[i])
	{
		cmd_path = ft_strjoin(split_paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

// This function first finds the occurence of "PATH=" in envp,
// then breakdown all the paths into "split_paths" 
char	**get_split_paths(char **envp)
{
	int		i;
	char	*env_path;
	char	**split_paths;

	i = 0;
	while (envp[i])
	{
		env_path = ft_strnstr(envp[i], "PATH=", 5);
		if (env_path)
		{
			env_path = ft_strdup(env_path);
			break ;
		}
		i++;
	}
	split_paths = ft_split(env_path, ':');
	free(env_path);
	return (split_paths);
}

// loop through env and attempt to find "PATH=" which contains all shell paths
// attempt to add cmd (e.g. ls) to each possible path and see if it exists
// if exists, returns the whole cmd path
char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**split_paths;
	char	*cmd_path;

	split_paths = get_split_paths(envp);
	i = 0;
	while (split_paths[i])
	{
		split_paths[i]= ft_strjoin(split_paths[i], "/");
		i++;
	}
	cmd_path = check_cmd_path(split_paths, cmd);
	if (!cmd_path)
	{
		free_all_paths(split_paths);
		return (NULL);
	}
	return (cmd_path);
}

int	init_pipex(struct s_pipex *pipex, int argc, char **argv)
{
	pipex = malloc(sizeof(t_pipex) * 1);
	pipex->status = 0;
	pipex->fd_infile = open(argv[1], O_RDONLY);
	if (pipex->fd_infile < 0)
		printf("FAILED FD INFILE");
	pipex->fd_outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->fd_outfile < 0)
		printf("FAILED FD OUTFILE");
	if (pipe(pipex->pipe) < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	struct s_pipex	pipex;

	if (init_pipex(&pipex, argc, argv) == -1)
		return (-1);
	// has bug if pipe() here
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		return (-1);
	if (pipex.pid1 == 0)
	{
		// child 1 process
		init_child_one(&pipex, argv, envp);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		return (-2);
	if (pipex.pid2 == 0)
	{
		// child 2 process
		usleep(5000000);
		init_child_two(&pipex, argv, envp);
	}
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	close(pipex.fd_infile);
	close(pipex.fd_outfile);
	waitpid(pipex.pid1, 0, 0);
	waitpid(pipex.pid2, 0, 0);
	printf("\n\nPIPEX DONE!!\n");
	return (0);
}
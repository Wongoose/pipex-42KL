#include "pipex.h"
#include <strings.h>
#include <stdio.h>

//loop through env and attempt to find "PATH=" which contains all shell paths
//attempt to add cmd (e.g. ls) to each possible path and see if it exists
//if exists, returns the whole cmd path
char	*get_cmd_path(char *cmd, char **envp)
{
	int	i;
	char	*env_path;
	char	**split_paths;
	char	*cmd_path;

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
	i = 0;
	while (split_paths[i])
	{
		split_paths[i]= ft_strjoin(split_paths[i], "/");
		i++;
	}
	i = 0;
	while (split_paths[i])
	{
		cmd_path = ft_strjoin(split_paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	// haven't found cmd path
	i = 0;
	while (split_paths[i])
		free(split_paths[i++]);
	free(split_paths);
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	**options; 
	char	*cmd;
	char	*cmd_path;
	// (void)argc;
	// (void)argv;
	cmd = argv[1];
	cmd_path = get_cmd_path(cmd, envp);
	if (!cmd_path)
	{
		printf("ERROR: No command path found!");
		return (0);
	}
	// check options length
	options = (char **)malloc(sizeof(char *) * 4);
	options[0] = argv[1];
	options[1] = argv[2];
	options[2] = argv[3];
	options[3] = NULL;
	execve(cmd_path, options, envp);
	printf("VIctory!");
	// printf("\nENV IS:\n%s\n", envp[24]);
	return (0);
}
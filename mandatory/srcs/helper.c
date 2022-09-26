/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:04:16 by zwong             #+#    #+#             */
/*   Updated: 2022/09/22 11:07:07 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

// Find "PATH=" in environment variables
// then breakdown all the paths into array of strings 
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
	i = 0;
	while (split_paths[i])
	{
		split_paths[i] = ft_strjoin(split_paths[i], "/");
		i++;
	}
	free(env_path);
	return (split_paths);
}

// After splitting possible paths
// Attempt to add cmd (e.g. ls) to each possible path and see if it exists
// if exists, returns the whole cmd path
char	*get_cmd_path(char *cmd, char **envp)
{
	char	**split_paths;
	char	*cmd_path;

	split_paths = get_split_paths(envp);
	cmd_path = check_cmd_path(split_paths, cmd);
	if (!cmd_path)
	{
		free_all_paths(split_paths);
		return (NULL);
	}
	return (cmd_path);
}

// Function runs directly from each child
// Get command path of the given command
// (each shell command belongs somewhere in the computer)
// execve(): This is a built in function that runs shell commands!
// 1. Give the full command path
// 2. Give the arguments of the command (e.g. "ls -la")
// 3. Give the built-in envronment pointer variable
// VOILA: Shell command will be executed!
void	execute_cmd(struct s_pipex *pipex, char **envp)
{
	char	*cmd;
	char	*cmd_path;

	cmd = pipex->cmd_args[0];
	cmd_path = get_cmd_path(cmd, envp);
	if (!cmd_path)
		err_exit("Failed to get command path");
	execve(cmd_path, pipex->cmd_args, envp);
}

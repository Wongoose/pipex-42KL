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

#include "includes/pipex.h"

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

// This function first finds the occurence of "PATH=" in envp,
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
		split_paths[i] = ft_strjoin(split_paths[i], "/");
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

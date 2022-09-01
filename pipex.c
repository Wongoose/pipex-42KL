#include "pipex.h"
#include <strings.h>
#include <stdio.h>

//loop through env and attempt to find "PATH=" which contains all shell paths
//attempt to add cmd (e.g. ls) to each possible path and see if it exists
//if exists, returns the whole cmd path
char	*get_cmd_path(char *cmd, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	// char	*options[3] = {argv[1], argv[2], NULL};

	(void)argc;
	(void)argv;
	// execve("/bin/ls", options, envp);
	printf("\nENV IS:\n%s\n", envp[1]);
	return (0);
}
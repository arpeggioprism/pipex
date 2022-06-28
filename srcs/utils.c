/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 02:25:22 by jshin             #+#    #+#             */
/*   Updated: 2022/06/29 05:49:01 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (0);
}

void	error_exit(char c)
{
	if (c == 'c')
	{
		ft_putstr_fd("[Error] Too many or too few arguments: ", 2);
		ft_putstr_fd("e.g. ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	else if (c == 'p')
		perror("[Error] Failed to pipe");
	else if (c == 'f')
		perror("[Error] Failed to fork");
	else if (c == 'd')
		perror("[Error] Failed to dup2");
	else if (c == 'o')
		perror("[Error] Failed to open");
	else if (c == 'e')
		perror("[Error] Failed to execve");
	else if (c == 'a')
		perror("[Error] Failed to access");
	exit(1);
}

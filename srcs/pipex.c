/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:10:14 by jshin             #+#    #+#             */
/*   Updated: 2022/06/29 17:53:53 by jshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, char **envp, int *fd);
void	parent_process(char **argv, char **envp, int *fd);

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		error_exit('c');
	if (pipe(fd) == -1)
		error_exit('p');
	pid = fork();
	if (pid == -1)
		error_exit('f');
	else if (pid == 0)
		child_process(argv, envp, fd);
	waitpid(pid, NULL, 0);
	parent_process(argv, envp, fd);
	return (0);
}

void	child_process(char **argv, char **envp, int *fd)
{
	int		filein;
	int		i;
	char	**cmd;
	char	*path;

	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error_exit('d');
	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		error_exit('o');
	if (dup2(filein, STDIN_FILENO) == -1)
		error_exit('d');
	cmd = ft_split(argv[2], ' ');
	path = find_path(cmd[0], envp);
	i = 0;
	if (!path)
	{
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
		error_exit('a');
	}
	if (execve(path, cmd, envp) == -1)
		error_exit('e');
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int		fileout;
	int		i;
	char	**cmd;
	char	*path;

	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_exit('d');
	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (fileout == -1)
		error_exit('o');
	if (dup2(fileout, STDOUT_FILENO) == -1)
		error_exit('d');
	cmd = ft_split(argv[3], ' ');
	path = find_path(cmd[0], envp);
	i = 0;
	if (!path)
	{
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
		error_exit('a');
	}
	if (execve(path, cmd, envp) == -1)
		error_exit('e');
}

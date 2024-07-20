/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:16:14 by fli               #+#    #+#             */
/*   Updated: 2024/07/12 16:14:37 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	cmd1_fd_manager(char **argv, t_pids	*new_nod)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		close_pipe(new_nod->pipefd);
		free(new_nod);
		return (infile_check(errno));
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (-1);
	close(fd_in);
	if (dup2((new_nod)->pipefd[1], STDOUT_FILENO) == -1)
		return (-1);
	close_pipe((new_nod)->pipefd);
	return (0);
}

int	cmd2_fd_manager(int ci, char **av, t_pids *nnod, t_pids **pidl)
{
	int	fd_out;

	fd_out = open(av[ci + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		close_pipe((nnod)->pipefd);
		ft_lstclear_pipex(pidl);
		exit(4);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (-1);
	close(fd_out);
	close_pipe((nnod)->pipefd);
	return (0);
}

int	infile_check(int err)
{
	if (err == EACCES)
		return (2);
	if (err == ENOENT)
		return (3);
	return (0);
}

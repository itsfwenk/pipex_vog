/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_cmd_manager_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:49:20 by fli               #+#    #+#             */
/*   Updated: 2024/07/12 16:12:45 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	cmd_middle_child(int *cmd_i, t_pids	**pidl, char **av, char **env)
{
	pid_t	pid_i;
	t_pids	*new_nod;

	new_nod = ft_lstnew_pipex((*cmd_i)++);
	if (new_nod == NULL)
		fail_cleaner(av, pidl);
	ft_lstadd_back_pipex(pidl, new_nod);
	if (pipe((new_nod)->pipefd) == -1)
		fail_cleaner(av, pidl);
	pid_i = fork();
	if (pid_i == -1)
		fail_cleaner(av, pidl);
	if (pid_i == 0)
	{
		if (cmd_fd_manager(new_nod) == -1)
			return (ft_lstclear_pipex(pidl), -1);
		if (cmd_middle_exec(new_nod->cmd_i, av, env, pidl) == -1)
			return (close_and_clear(new_nod->pipefd, pidl), -1);
	}
	if (dup2(new_nod->pipefd[0], STDIN_FILENO) == -1)
		return (close_and_clear(new_nod->pipefd, pidl), -1);
	close_pipe(new_nod->pipefd);
	new_nod->p_id = pid_i;
	return (new_nod->status);
}

static void	exec_cmd_fail(char **cmd, char *cmd_path, t_pids	**pid_list)
{
	free_split(cmd);
	free(cmd_path);
	ft_lstclear_pipex(pid_list);
}

static void	cmd_middle_exec_part2(char **cmd, char **envp, t_pids	**pid_list)
{
	char	*cmd_path;

	cmd_path = get_pathname(envp, cmd[0]);
	if (cmd_path == NULL)
	{
		free_split(cmd);
		ft_lstclear_pipex(pid_list);
		exit(-1);
	}
	if (cmd_exec(cmd, cmd_path, envp) == -1)
	{
		exec_cmd_fail(cmd, cmd_path, pid_list);
		exit(EXIT_FAILURE);
	}
}

int	cmd_middle_exec(int cmd_i, char **argv, char **envp, t_pids	**pid_list)
{
	char	**cmd;

	if (argv[cmd_i][0] == '\0')
	{
		ft_lstclear_pipex(pid_list);
		exit(5);
	}
	cmd = ft_split(argv[cmd_i], ' ');
	if (cmd == NULL)
	{
		ft_lstclear_pipex(pid_list);
		exit(EXIT_FAILURE);
	}
	cmd_middle_exec_part2(cmd, envp, pid_list);
	return (0);
}

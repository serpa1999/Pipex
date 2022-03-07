/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshor <rshor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:54:07 by rshor             #+#    #+#             */
/*   Updated: 2022/03/05 18:03:34 by rshor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_error_dup(t_pipex *pipex)
{
	ft_free_pipex(pipex);
	perror("./pipex");
	exit(ERR_DUP);
}

static void	ft_child_0_help(t_pipex **pipex, char **argv)
{
	if (dup2((*pipex)->infile_fd, STDIN_FILENO) == -1)
	{
		ft_close_file((*pipex)->infile_fd, *argv);
		ft_close_file((*pipex)->fd[1], NULL);
		ft_error_dup((*pipex));
	}
	if (dup2((*pipex)->fd[1], STDOUT_FILENO) == -1)
	{
		ft_close_file((*pipex)->infile_fd, *argv);
		ft_close_file((*pipex)->fd[1], NULL);
		ft_error_dup((*pipex));
	}
}

void	ft_child_0(t_pipex	*pipex, char **argv, char **envp)
{
	ft_close_file(pipex->outfile_fd, argv[4]);
	ft_close_file(pipex->fd[0], NULL);
	if (pipex->infile_fd == -1)
	{
		ft_free_pipex(pipex);
		ft_close_file(pipex->fd[1], NULL);
		exit (ERR_FILE);
	}
	ft_child_0_help(&pipex, &(argv[1]));
	ft_close_file(pipex->infile_fd, argv[1]);
	ft_close_file(pipex->fd[1], NULL);
	ft_exec_without_path(pipex, envp, pipex->cmd1);
	ft_exec_with_path(pipex, envp, pipex->cmd1);
	ft_error(pipex->cmd1[0], "Command not found");
	ft_free_pipex(pipex);
	exit(ERR_EXECUTE_CMD);
}

void	ft_child_1_help(t_pipex **pipex, char **argv)
{
	if ((*pipex)->outfile_fd == -1)
	{
		ft_free_pipex((*pipex));
		ft_close_file((*pipex)->fd[0], NULL);
		exit (ERR_FILE);
	}
	if (dup2((*pipex)->fd[0], STDIN_FILENO) == -1)
	{
		ft_close_file((*pipex)->outfile_fd, *argv);
		ft_close_file((*pipex)->fd[0], NULL);
		ft_error_dup((*pipex));
	}
	if (dup2((*pipex)->outfile_fd, STDOUT_FILENO) == -1)
	{
		ft_close_file((*pipex)->outfile_fd, *argv);
		ft_close_file((*pipex)->fd[0], NULL);
		ft_error_dup((*pipex));
	}
}

void	ft_child_1(t_pipex	*pipex, char **argv, char **envp)
{
	ft_close_file(pipex->infile_fd, argv[1]);
	ft_close_file(pipex->fd[1], NULL);
	ft_child_1_help(&pipex, &(argv[4]));
	ft_close_file(pipex->outfile_fd, argv[4]);
	ft_close_file(pipex->fd[0], NULL);
	ft_exec_without_path(pipex, envp, pipex->cmd2);
	ft_exec_with_path(pipex, envp, pipex->cmd2);
	ft_error(pipex->cmd2[0], "Command not found");
	ft_free_pipex(pipex);
	exit(ERR_EXECUTE_CMD);
}

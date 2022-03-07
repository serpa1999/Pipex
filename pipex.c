/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshor <rshor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:52:31 by rshor             #+#    #+#             */
/*   Updated: 2022/03/06 11:32:25 by rshor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *name, char *str_error)
{
	ft_putstr_fd("./pipex: ", 2);
	ft_putstr_fd(str_error, 2);
	if (name)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(name, 2);
	}
	ft_putstr_fd("\n", 2);
}

static void	ft_check_argc(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("./pipex: Incorrect count of args\n", 2);
		exit (ERR_NUMBER_ARG);
	}
}

static void	ft_waitpid(t_pipex *pipex, int *status_0, int *status_1)
{
	if (pipex->child[0] > 0)
	{
		if (waitpid(pipex->child[0], status_0, 0) == -1)
			ft_error(NULL, strerror(errno));
	}
	if (pipex->child[1] > 0)
	{
		if (waitpid(pipex->child[1], status_1, 0) == -1)
			ft_error(NULL, strerror(errno));
	}
}

static void	ft_print_errors(t_pipex pipex, char **argv)
{
	if (pipex.infile_fd == -1)
		ft_error(argv[1], strerror(errno));
	if (pipex.outfile_fd == -1)
		ft_error(argv[4], strerror(errno));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status[2];

	ft_check_argc(argc);
	if (pipe(pipex.fd) == -1)
	{
		perror("./pipex");
		exit(ERR_PIPE);
	}
	pipex.infile_fd = open(argv[1], O_RDONLY);
	pipex.outfile_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_parser(&pipex, argv, envp);
	ft_child(&pipex, argv, envp);
	ft_free_pipex(&pipex);
	ft_close_file(pipex.infile_fd, argv[1]);
	ft_close_file(pipex.outfile_fd, argv[4]);
	ft_close_file(pipex.fd[0], NULL);
	ft_close_file(pipex.fd[1], NULL);
	ft_waitpid(&pipex, &status[0], &status[1]);
	ft_print_errors(pipex, argv);
	if (WIFEXITED(status[1]) != 0)
		return (WEXITSTATUS(status[1]));
	return (0);
}

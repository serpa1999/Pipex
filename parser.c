/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshor <rshor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:53:00 by rshor             #+#    #+#             */
/*   Updated: 2022/03/05 17:53:03 by rshor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_get_path(char **envp)
{
	int		i;
	char	**bin_path;
	size_t	len;

	len = ft_strlen(PATH);
	if (!envp)
		return (NULL);
	if (!(*envp))
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], PATH, len))
			break ;
		i++;
	}
	bin_path = ft_split(envp[i] + len, ':');
	if (!bin_path)
	{
		perror("");
		exit (ERR_MEMORY_ALLOCATE);
	}
	return (bin_path);
}

static char	**ft_get_cmd(char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	return (cmd);
}

void	ft_parser(t_pipex *pipex, char **argv, char **envp)
{
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
	{
		ft_putstr_fd("ERR_READ_CMD\n", 2);
		exit(ERR_READ_CMD);
	}
	pipex->bin_path = ft_get_path(envp);
	pipex->cmd1 = ft_get_cmd(argv[2]);
	pipex->cmd2 = ft_get_cmd(argv[3]);
	if (!pipex->cmd1 || !pipex->cmd2)
	{
		ft_free_array(pipex->bin_path);
		perror("./pipex");
		exit (ERR_MEMORY_ALLOCATE);
	}
}

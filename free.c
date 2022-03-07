/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshor <rshor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:53:51 by rshor             #+#    #+#             */
/*   Updated: 2022/03/05 18:02:19 by rshor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_array(char **arr)
{
	int	i;
	int	number_str_in_array;

	i = 0;
	number_str_in_array = 0;
	while (arr[number_str_in_array] != NULL)
	{
		number_str_in_array++;
	}
	while (i < number_str_in_array)
		free(arr[i++]);
	free(arr);
}

void	ft_free_pipex(t_pipex *pipex)
{
	ft_free_array(pipex->bin_path);
	ft_free_array(pipex->cmd1);
	ft_free_array(pipex->cmd2);
}

void	ft_child(t_pipex *pipex, char **argv, char **envp)
{
	pipex->child[0] = fork();
	if (pipex->child[0] < 0)
	{
		perror ("./pipex");
		exit (ERR_FORK);
	}
	else if (pipex->child[0] == 0)
		ft_child_0(pipex, argv, envp);
	pipex->child[1] = fork();
	if (pipex->child[1] < 0)
	{
		perror ("./pipex");
		exit (ERR_FORK);
	}
	else if (pipex->child[1] == 0)
		ft_child_1(pipex, argv, envp);
}

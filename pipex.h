/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshor <rshor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:51:33 by rshor             #+#    #+#             */
/*   Updated: 2022/03/06 11:35:26 by rshor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>

# define ERR_NUMBER_ARG 1
# define ERR_MEMORY_ALLOCATE 2
# define ERR_FILE 3
# define ERR_READ_CMD 4
# define ERR_EXECUTE_CMD 5
# define ERR_FORK 6
# define ERR_DUP 7
# define ERR_EXEC 8
# define ERR_PIPE 9

# define PATH "PATH="

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	pid_t	child[2];
	char	**bin_path;
	char	**cmd1;
	char	**cmd2;
}		t_pipex;

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_slash(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

void	ft_parser(t_pipex *pipex, char **argv, char **envp);
void	ft_child(t_pipex *pipex, char **argv, char **envp);
void	ft_child_1(t_pipex	*pipex, char **argv, char **envp);
void	ft_child_1_help(t_pipex **pipex, char **argv);
void	ft_child_0(t_pipex	*pipex, char **argv, char **envp);

void	ft_open_files(t_pipex *pipex, char **argv);
void	ft_close_file(int fd, char *name);
void	ft_exec_without_path(t_pipex *pipex, char **envp, char **cmd);
void	ft_exec_with_path(t_pipex *pipex, char **envp, char **cmd);

void	ft_error(char *name, char *str_error);
void	ft_free_array(char **arr);
void	ft_free_pipex(t_pipex *pipex);

#endif
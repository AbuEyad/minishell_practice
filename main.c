/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:45:17 by habu-zua          #+#    #+#             */
/*   Updated: 2023/12/16 19:00:41 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/main.h"

void ft_free(char **cmd)
{
	int i;
	i = 0;
	while(cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *input;
	char **cmd;
	char *path;
	path = 0;
	int fd = open("test.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	close(fd);
	input = NULL;
	while (1)
	{
		input = readline("Hz$ ");// parsing 
		if (ft_strcmp(input, "exit") == 0)
			exit(0);
	   	cmd = ft_split(input, ' ');
		path = ft_strjoin("/bin/",cmd[0]);
	   	if (fork() == 0)
	   		execve(path, cmd, env);
		wait(NULL);
		free(path);
		ft_free(cmd);
	}
   
	return (0);
}

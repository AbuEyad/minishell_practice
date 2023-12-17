/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_old1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:45:17 by habu-zua          #+#    #+#             */
/*   Updated: 2023/12/17 14:18:49 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//***********
// path is hardcoded to /bin/ls
//***********
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
	free(cmd);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *input;
	char **cmd;
	char *path;

	path = 0;
	input = NULL;
	while (1)
	{
		input = readline("Prompt$ ");
		//take care of exit
		if (ft_strcmp(input, "exit") == 0)
			exit(0);
	   	cmd = ft_split(input, ' ');
		path = ft_strjoin("/bin/",cmd[0]);
		//you can run execuve without fork but this will exit the shell once the command is done.
	   	if (fork() == 0)
	   		execve(path, cmd, env);
		wait(NULL); //wait for child to finish.
		free(path);
		ft_free(cmd);
	}
   
	return (0);
}
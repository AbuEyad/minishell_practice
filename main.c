/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:45:17 by habu-zua          #+#    #+#             */
/*   Updated: 2023/12/31 13:26:21 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//***********
// path fixed
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

char *ft_getpath(char *cmd, char *envpath)
{
    int i;
    char **temp;
    char *path;
    char *temp2;
 
    temp = ft_split(envpath, ':');
    i = 0;
    while(temp[i])
    {
        temp2 = ft_strjoin(temp[i], "/");
        path = ft_strjoin(temp2, cmd);
        free(temp2);
        if (access(path, F_OK) == 0)
			return (ft_free(temp), path);
        free(path);
        i++;
    }
	ft_free(temp);
    return (NULL);
}

void print_cmd(char **cmd)
{
	int i;
	i = 0;
	while(cmd[i])
	{
		printf("cmd[%d] = %s\n", i, cmd[i]);
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
	input = NULL;
	while (1)
	{
		input = readline("Prompt$ ");
		//take care of exit
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0);
		}
	   	cmd = ft_split(input, ' ');
		
		print_cmd(cmd);
		//you can run execuve without fork but this will exit the shell once the command is done.
		path = ft_getpath(cmd[0], getenv("PATH"));
	   	if (fork() == 0)
	   	{
            execve(path, cmd, env);
            perror("execve"); // In case execve fails
            exit(EXIT_FAILURE); // Make sure child process exits on failure
        }
		else 
			wait(NULL);
		free(path);
		ft_free(cmd);
	}
	return (0);
}



/*
	this part to test leaks if file not closed.
	int fd = open("test.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	close(fd);

*/
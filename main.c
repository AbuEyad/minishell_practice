/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:45:17 by habu-zua          #+#    #+#             */
/*   Updated: 2024/01/05 16:54:46 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/main.h"

void execute_cmd(char **cmd, char **env)
{
	char *path;
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
		input = readline("$> ");
		ft_trim_input(&input);
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0);
		}
	   	cmd = ft_split(input, ' ');
		// ft_print_cmd(cmd);
		execute_cmd(cmd, env);
		ft_free(cmd);
	}
	return (0);
}



/*
	this part to test leaks if file not closed.
	int fd = open("test.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	close(fd);

*/
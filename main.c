/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:45:17 by habu-zua          #+#    #+#             */
/*   Updated: 2023/12/16 16:59:00 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/main.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int i;
	char *input;
	char **cmd;
	
	input = NULL;
	i = 0;
	while (1)
	{
		input = readline("Hz$ ");// parsing 
		if (ft_strcmp(input, "exit") == 0)
			exit(0);
	   	cmd = ft_split(input, ' ');
	   	if (fork() == 0)
	   		execve(ft_strjoin("/bin/",cmd[0]) , cmd, env);
		wait(NULL);
	}
   
	return (0);
}

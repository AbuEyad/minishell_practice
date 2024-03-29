/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habu-zua <habu-zua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:03:49 by tpons             #+#    #+#             */
/*   Updated: 2024/01/08 22:45:51 by habu-zua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// #include <term.h>
#include <curses.h>
#include <termios.h>
#include <stdint.h>
#include <sys/ioctl.h>

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include "libft/libft.h"

typedef	struct	s_data
{
	char		**env;
	int			fd_in;
	int			fd_out;
	char		*pwd;
	int			redir;
}				t_data;

int				g_status;
char			*g_user_input;
int				g_quit;

int				envlen(char **env);
void			free_env(char **env);
char			**dup_env(char **env);
void			close_fds(t_data *data);

int				parser_start(char *str, t_data *data);
void			quote_len(char **str, int *i, char quote);
char			**input_split(char *str);

int				handle_basic(char *clean_input, t_data *data, int piped);
void			handle_echo(char **args);
void			handle_cd(char **args, t_data *data);
void			handle_unset(char **inputs, t_data *data);

char			**export_env(char **old_env, char *export);
void			handle_env(char **env);

int				change_pwd(t_data *data, char *input);
void			handle_pwd(t_data *data);

int				is_relative(char *str);
char			**gen_paths(int index, t_data *data, char *input);
int				check_exec(char **inputs, t_data *data);
void			handle_exec(char **args, t_data *data);

void			replace_var(char *new_var, t_data *data, int index);
int				var_index(char *name, t_data *data);
int				print_export(char **env);
int				check_export(char *str);
char			**copy_export_env(char **env);
void			handle_export(char **args, t_data *data);

int				handle_pipe(char *input1, char *input2, t_data *data);
int				parser_delegator(char *input, t_data *data, int piped);
int				parser_error(char *str);
void			parser_variable(char **input_address, int *i, t_data *data);
int				parser_redir(char **input_address, t_data *data);
void			should_escape(int *i, char *str);
void			handle_redir(char **input_address, int i, t_data *data);
void			remove_redir_input(char **input_address, int i, int j);
int				get_name_len(char *str);
char			*get_filename(char *str, int *j);
void			input_copy(char *dst, char *src);
char			*input_cleaner(char *str);
void			copy_newsplit(char *src, char *dst, char quote);
void			escape_char(char **dst, char **src);

void			sig_exec_init(void);
void			sig_init(void);

void			error_sentence(char *str, int status);
void			handle_exit(char **inputs, t_data *data);

#endif

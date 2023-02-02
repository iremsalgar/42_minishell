/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okavak <okavak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:30:35 by okavak            #+#    #+#             */
/*   Updated: 2023/02/02 00:56:14 by okavak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

// check_redirections
int				check_redirections(t_simple_cmds *cmd);

// executor
int				executor(t_tools *tools);
t_simple_cmds	*call_expander(t_tools *tools, t_simple_cmds *cmd);
int				pipe_wait(int *pid, int amount);
void			fork_redirect(t_tools *tools, int end[2], int fd_in);

// handle_cmd
int				find_cmd(t_simple_cmds *cmd, t_tools *tools);
void			handle_cmd(t_simple_cmds *cmd, t_tools *tools);
void			dup_cmd(t_simple_cmds *cmd, t_tools *tools,
					int end[2], int fd_in);
void			single_cmd(t_simple_cmds *cmd, t_tools *tools);
int				ft_fork(t_tools *tools, int end[2], int fd_in,
					t_simple_cmds *cmd);

// heredoc
int				send_heredoc(t_tools *tools, t_simple_cmds *cmd);
#endif

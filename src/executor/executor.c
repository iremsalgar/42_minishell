#include "executor.h"

/*
* It expands the string of the command and
* the strings of the redirections
*/
t_simple_cmds	*call_expander(t_tools *tools, t_simple_cmds *cmd)
{
	t_lexer	*start;

	cmd->str = expander(tools, cmd->str);
	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token != LESS_LESS)
			cmd->redirections->str
				= expander_str(tools, cmd->redirections->str);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	if (str_control(tools))
	{
		g_global.error_num = cmd_not_found(tools->simple_cmds->str[0]);
		reset_tools(tools);
		return (NULL);
	}
	return (cmd);
}

/*It waits for all the processes to finish */
int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

/*It forks the process and duplicates the command*/
int	ft_fork(t_tools *tools, int end[2], int fd_in, t_simple_cmds *cmd)
{
	static int	i = 0;

	if (tools->reset == true)
	{
		i = 0;
		tools->reset = false;
	}
	tools->pid[i] = fork();
	if (tools->pid[i] < 0)
		ft_error(5, tools);
	if (tools->pid[i] == 0)
		dup_cmd(cmd, tools, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

/*It checks if the current command is a heredoc,
and if so, it closes the read end of the pipe and
opens the heredoc file for reading*/
int	check_fd_heredoc(t_tools *tools, int end[2], t_simple_cmds *cmd)
{
	int	fd_in;

	if (tools->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

/*It forks and executes the commands in the pipeline*/
int	executor(t_tools *tools)
{
	int		end[2];
	int		fd_in;

	fd_in = STDIN_FILENO;
	while (tools->simple_cmds)
	{
		tools->simple_cmds = call_expander(tools, tools->simple_cmds);
		if (tools != NULL && tools->simple_cmds != NULL && \
			tools->simple_cmds->next != NULL)
			pipe(end);
		fork_redirect(tools, end, fd_in);
		close(end[1]);
		if (tools == NULL || tools->simple_cmds == NULL)
			return (0);
		if (tools->simple_cmds->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(tools, end, tools->simple_cmds);
		if (tools->simple_cmds->next)
			tools->simple_cmds = tools->simple_cmds->next;
		else
			break ;
	}
	pipe_wait(tools->pid, tools->pipes);
	tools->simple_cmds = ft_simple_cmdsfirst(tools->simple_cmds);
	return (0);
}

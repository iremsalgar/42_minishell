#include "minishell.h"

int	minishell_loop(t_tools *tools);

/*It initializes the tools structure, which is used to store the shell's state*/
int	implement_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->lexer_list = NULL;
	tools->reset = false;
	tools->pid = NULL;
	tools->heredoc = false;
	g_global.stop_heredoc = 0;
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	g_global.sig_quit = 0;
	parse_envp(tools);
	init_signals();
	return (1);
}

/*It resets the tools struct to its initial state
and the function is takes everything to the recursive*/
int	reset_tools(t_tools *tools)
{
	ft_simple_cmdsclear(&tools->simple_cmds);
	free(tools->args);
	if (tools->pid)
		free(tools->pid);
	free_arr(tools->paths);
	implement_tools(tools);
	tools->reset = true;
	minishell_loop(tools);
	return (1);
}

/*
* It creates a pipe for each pipe in the command,
* forks a child process for each pipe, and executes
* the command in the child process
*/
int	prepare_executor(t_tools *tools)
{
	signal(SIGQUIT, sigquit_handler);
	g_global.in_cmd = 1;
	if (tools->pipes == 0)
		single_cmd(tools->simple_cmds, tools);
	else
	{
		tools->pid = ft_calloc(sizeof(int), tools->pipes + 2);
		if (!tools->pid)
			return (ft_error(1, tools));
		executor(tools);
	}
	g_global.in_cmd = 0;
	return (EXIT_SUCCESS);
}
/*
* Minishell loop works like recursive
* Then the line that comes from readline,
* function going to be put in tools->args.
* tmp will be trimmed about the spaces of the string,
* the spaces which has will be in beginning and end of the args line
* then the function's way goes to the if situations
* the first if situation works for the ctrl + d (EOF) signal
* the line of tools->args will be added on history
*/

int	minishell_loop(t_tools *tools)
{
	char	*tmp;

	tools->args = readline(READLINE_MSG);
	tmp = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = tmp;
	if (!tools->args)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (tools->args[0] == '\0')
		return (reset_tools(tools));
	add_history(tools->args);
	if (!count_quotes(tools->args))
		return (ft_error(2, tools));
	control_pipe(tools);
	if (!token_reader(tools))
		return (ft_error(1, tools));
	parser(tools);
	prepare_executor(tools);
	reset_tools(tools);
	return (1);
}

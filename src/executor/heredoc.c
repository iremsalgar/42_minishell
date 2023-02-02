#include "../../includes/executor.h"

/*
* It creates a file with the name of the heredoc token,
* and writes to it the lines that the user inputs
* until the user inputs the heredoc token
*/
int	create_heredoc(t_lexer *heredoc, bool quotes,
	t_tools *tools, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_MSG);
	while (line && !g_global.stop_heredoc && \
		ft_strncmp(heredoc->str, line, ft_strlen(line) + 1))
	{
		if (quotes == false)
			line = expander_str(tools, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	free(line);
	if (g_global.stop_heredoc)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

/*It creates a heredoc file*/
int	ft_heredoc(t_tools *tools, t_lexer *heredoc, char *file_name)
{
	bool	quotes;
	int		sl;

	sl = EXIT_SUCCESS;
	if ((heredoc->str[0] == '\"'
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\"')
		|| (heredoc->str[0] == '\''
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	if (there_is_quotes(heredoc->str))
	{
		delete_quotes(heredoc->str);
		delete_quotes(heredoc->str);
	}
	g_global.stop_heredoc = 0;
	g_global.in_heredoc = 1;
	sl = create_heredoc(heredoc, quotes, tools, file_name);
	g_global.in_heredoc = 0;
	tools->heredoc = true;
	return (sl);
}

/*
* It generates a filename for a temporary file
* that will be used to store the contents of a heredoc
*/
char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

/*It sends the heredoc to a file*/
int	send_heredoc(t_tools *tools, t_simple_cmds *cmd)
{
	t_lexer	*start;
	int		sl;

	if (cmd == NULL)
		return (EXIT_SUCCESS);
	start = cmd->redirections;
	sl = EXIT_SUCCESS;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == LESS_LESS)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_filename();
			sl = ft_heredoc(tools, cmd->redirections, cmd->hd_file_name);
			if (sl)
			{
				g_global.error_num = 1;
				return (reset_tools(tools));
			}
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}

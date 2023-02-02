#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	if (argc != 1 || argv[1])
	{
		printf("\x1b[31m This program does not accept arguments\x1b[0m \n");
		exit(0);
	}
	tools.envp = ft_arrdup(envp);
	find_pwd(&tools);
	implement_tools(&tools);
	printf("\n%s\n\n", WELCOME_MSG);
	minishell_loop(&tools);
	return (0);
}
/*
* First of all main's envp will be copied in tools struct
* after inside of the tools struct program going to find pwd and old_pwd
* then program will implement the tools struct.
* program will find the path and copies it and make the process
* with split then program will put the path to the tools path
*/

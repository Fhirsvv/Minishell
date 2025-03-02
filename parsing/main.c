/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:52:41 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 20:54:16 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

//#define TOKENS

#ifdef TOKENS
#define TOKENS
static const char	*get_token_type_name(int symbol)
{
	switch (symbol)
	{
	case PIPE:
		return "PIPE";
	case REDIR_D:
		return "REDIR_D";
	case DOBLE_REDIR_D:
		return "DOBLE_REDIR_D";
	case REDIR_I:
		return "REDIR_I";
	case HERE_DOC:
		return "HERE_DOC";
	case WORD:
		return "WORD";
	case D_QUOTE:
		return "D_QUOTE";
	case S_QUOTE:
		return "S_QUOTE";
	default:
		return "UNKNOWN";
	}
}
static void	print_tokens(t_myshell *tshell)
{
	t_token *current_token;

	current_token = tshell->tokens;
	while (current_token)
	{
		printf("Token: %s \nType: %s\n", current_token->content,
			   get_token_type_name(current_token->symbol));
		current_token = current_token->next;
	}
}

#endif

/*static void print_comands(t_myshell *tsh)
{
	t_comand *aux = tsh->comands;
	int i = 0;

	if (!aux)
		printf("no hay comands\n");
	while (aux)
	{
		printf("_______________________________________________\n");
		while (aux->args[i])
		{
			printf("ARG %i: %s\n",i+1, aux->args[i]);
			i++;
		}
		i = 0;
		int k;
		if (tsh->comands->fds->apend_file)
			for(k = 0; tsh->comands->fds->apend_file[k]; k++)
				printf("APPEND FILE: %s\n", tsh->comands->fds->apend_file[k]);
		if (tsh->comands->fds->apend_file)
			for(k = 0; tsh->comands->fds->input_file[k]; k++)
				printf("INPUT FILE: %s\n", tsh->comands->fds->input_file[k]);
		if (tsh->comands->fds->apend_file)
			for(k = 0; tsh->comands->fds->output_file[k]; k++)
				printf("OUTPUT FILE: %s\n", tsh->comands->fds->output_file[k]);
		printf("FD IN: %d\n", tsh->comands->fds->fd_in);
		printf("FD: OUT %d\n", tsh->comands->fds->fd_out);
		printf("_______________________________________________\n");
		aux = aux->next;
	}
	//printf("\n\n");
	return ;
}*/

int	main(int argc, char **argv, char **env)
{
	t_myshell	tshell;

	(void)argv;
	if (argc != 1)
	{
		write(1, "MINISHELL does not accept arguments\n", 37);
		return (1);
	}
	signals();
	init(&tshell, env);
	while (loop(&tshell))
	{}
	exit_minishell(&tshell);
	return (0);
}

//ctrl + D es EOF, para eso lo de !pr -> break
int	loop(t_myshell *tshell)
{
	char	*pr;

	pr = NULL;
	while (1)
	{
		pr = readline("MINISHELL$ ");
		if (!pr)
			break ;
		tshell->prompt = ft_strtrim(pr, " \n\t\r\v\f");
		ft_free(pr);
		parsing(tshell);
		//exec(tshell);
		free_minishell(tshell);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:00:23 by ecortes-          #+#    #+#             */
/*   Updated: 2025/02/03 11:11:53 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	init(t_myshell *myshell, char **environ)
{
	myshell->tokens = NULL;
	myshell->environ = ft_array_duplicate(environ);
	myshell->prompt = NULL;
	myshell->path = get_path(myshell);
	myshell->comands = NULL;
	return(0);
}

void	init_fds(t_fds **fds)
{
	*fds = malloc(sizeof(t_fds));
	if (!(*fds))
		return ;
	(*fds)->apend_file = NULL;
	(*fds)->input_file = NULL;
	(*fds)->output_file = NULL;
	(*fds)->fd_in = -1;
	(*fds)->fd_out = -1;
	(*fds)->stdin_backup = dup(STDIN_FILENO);
	(*fds)->stdout_backup = dup(STDOUT_FILENO);
}

t_token_handler	init_token_handler(char *str, t_myshell *ms)
{
	t_token_handler	h;

	h.i = 0;
	h.str = str;
	h.quote = 0;
	h.start_q = NULL;
	h.ms = ms;
	return (h);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:00:23 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 19:33:56 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	init(t_myshell *myshell, char **environ)
{
	myshell->tokens = NULL;
	myshell->environ = ft_array_duplicate(environ);
	myshell->prompt = NULL;
	myshell->path = get_path(myshell);
	myshell->t_com = NULL;
	myshell->exit_status = 0;
	return(0);
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

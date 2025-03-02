/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:41:22 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 20:00:58 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	trim_quotes(t_myshell *ms)
{
	t_token *aux;
	char *to_free;

	if (ms->exit_status != EXIT_SUCCESS)
		return (ms->exit_status);
	aux = ms->tokens;
	while (aux)
	{
		if (aux->symbol == D_QUOTE)
		{
			to_free = aux->content;
			aux->content = ft_strtrim(aux->content, "\"");
			if (!aux->content)
				return (1);
			free(to_free);
		}
		aux = aux->next;
	}
	return (0);
}

int is_token(char c)
{
	return (c == '<' || c == '|' || c == '>');
}
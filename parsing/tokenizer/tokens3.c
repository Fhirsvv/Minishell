/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:41:22 by ecortes-          #+#    #+#             */
/*   Updated: 2025/02/06 13:45:07 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	trim_quotes(t_myshell *ms)
{
	t_token *aux;
	char *to_free;

	aux = ms->tokens;
	while (aux)
	{
		if (aux->symbol == D_QUOTE)
		{
			to_free = aux->content;
			aux->content = ft_strtrim(aux->content, "\"");
			free(to_free);
		}
		aux = aux->next;
	}
}
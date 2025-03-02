/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:34:24 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 20:00:21 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int	count_quotes(const char *prompt)
{
	char	quote_char;
	int		quotes;
	int		i;

	quote_char = '\0';
	quotes = 0;
	i = 0;
	while (prompt[i] != '\0')
	{
		if ((prompt[i] == '\'' || prompt[i] == '"') && quote_char == '\0')
		{
			quote_char = prompt[i];
			quotes++;
		}
		else if ((prompt[i] == '\'' || prompt[i] == '"') &&
				quote_char == prompt[i])
		{
			quote_char = '\0';
			quotes++;
		}
		i++;
	}
	if (quotes % 2 != 0 || quotes == 1)
		return (1);
	return (0);
}

int	how_many_finds(char *str, int c)
{
	char	*aux;
	int		count;

	count = 0;
	aux = str;
	while (1)
	{
		aux = ft_strchr(aux, c);
		if (!aux)
			return (count);
		aux++;
		count++;
	}
	return (count);
}

int parsing(t_myshell *tshell)
{
	if (!tshell->prompt)
		tshell->exit_status = 1;

	add_history(tshell->prompt);
	if (count_quotes(tshell->prompt) == 1)
	{
		free(tshell->prompt);
		tshell->exit_status = 1;
		return (tshell->exit_status);
	}
	tokens2(tshell);
	ft_expander(tshell);
	ft_comand(tshell);
	ft_path(tshell);
	return (0);
}

void	exit_minishell(t_myshell *ms)
{
	if (ms->environ)
		free_arr(ms->environ);
	if (ms->t_com)
		free_tcoms(ms);
}

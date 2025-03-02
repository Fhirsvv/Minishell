/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:39:27 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 20:00:44 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	update_last_token_symbol(t_myshell *tshell, int new_symbol)
{
	t_token	*current;

	current = tshell->tokens;
	if (tshell == NULL || tshell->tokens == NULL)
		return ;
	while (current->next != NULL)
		current = current->next;
	current->symbol = new_symbol;
}

int	token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, ">") == 0)
		return (REDIR_D);
	else if (ft_strcmp(str, ">>") == 0)
		return (DOBLE_REDIR_D);
	else if (ft_strcmp(str, "<") == 0)
		return (REDIR_I);
	else if (ft_strcmp(str, "<<") == 0)
		return (HERE_DOC);
	else if (str[0] == '"')
		return (D_QUOTE);
	else if (str[0] == '\'')
		return (S_QUOTE);
	else
		return (WORD);
}

int	add_token_free(t_token_handler *h, t_myshell *ms)
{
	char	*buff;

	buff = NULL;
	if (h->start_q)
	{
		buff = ft_substr(h->str, h->start_q - h->str, &h->str[h->i] - h->start_q);
		if (!buff)
			return (1); // ver cual seria
		ft_tokenadd_back(&ms->tokens, ft_token_new(buff, token_type(buff)));
		ft_free(buff);
	}
	h->start_q = NULL;
	return (0);
}

int	take_quotes(t_myshell *ms)
{
	t_token *aux;
	char *str;

	str = NULL;
	aux = ms->tokens;
	while (aux)
	{
		if (aux->symbol == D_QUOTE || aux->symbol == S_QUOTE)
		{
			if (aux->symbol == D_QUOTE)
			{
				str = ft_strtrim(aux->content, "\"");
				if (!str)
					return (1);
			}
			else
			{
				str = ft_strtrim(aux->content, "'");
				if (!str)
					return (1);
			}
			free(aux->content);
			aux->content = str;
			str = NULL;
		}
		aux = aux->next;
	}
	return (0);
}

void	split_various_dolar(t_myshell *tshell)
{
	t_token	*aux;
	t_token	*new;
	t_token	*next;
	char	**arr;
	int		i;

	aux = tshell->tokens;
	while (aux)
	{
		next = aux->next;
		if ((aux->symbol == WORD || aux->symbol == D_QUOTE)
			&& how_many_finds(aux->content, '$') > 1)
		{
			arr = ft_split(aux->content, '$');
			if (!arr)
				return ;
			new = ft_token_new(ft_strjoin("$", arr[0]), WORD);
			ft_tokensubstitute(&tshell->tokens, new, aux);
			i = 1;
			ft_add_after(tshell, arr, new, &i);
		}
		aux = next;
	}
}

void	ft_add_after(t_myshell *tshell, char **arr, t_token *new, int *i)
{
	while (arr[*i])
	{
		ft_tokenadd_after(&tshell->tokens,
			ft_token_new(ft_strjoin("$", arr[*i]), WORD), new);
		new = new->next;
		*i = *i + 1;
	}
}

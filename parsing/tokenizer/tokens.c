/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:08:06 by ecortes-          #+#    #+#             */
/*   Updated: 2025/03/02 19:42:21 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static int is_quote(char c)
{
	return (c == '"' || c == '\'');
}

static void	handle_tokens(t_token_handler *h, t_myshell *ms)
{
	h->start_q = &h->str[h->i];
	if (h->str[h->i] == h->str[h->i + 1])
	{
		h->i += 2;
		add_token_free(h, ms);
	}
	else
	{
		h->i += 1;
		add_token_free(h, ms);
	}
	h->i--;
}

static void exit_quotes(t_token_handler *h, t_myshell *ms)
{
	h->i++;
	add_token_free(h, ms);
	h->i--;
	h->quote = 0;
}

int	tokens2(t_myshell *ms)
{
	t_token_handler	h;

	h = init_token_handler(ms->prompt, ms);
	while (h.str[h.i])
	{
		if (!h.start_q && h.str[h.i] != ' ' && !is_token(h.str[h.i]))
		{
			h.start_q = &h.str[h.i];
			if (is_quote(h.str[h.i]))
				h.quote = h.str[h.i];
		}
		else if (h.start_q && !h.quote && (is_quote(h.str[h.i]) || is_token(h.str[h.i]) || h.str[h.i] == ' '))
		{
			if (add_token_free(&h, ms))
				return (1);
			continue ;
		}
		else if (h.quote && h.str[h.i] == h.quote)
			exit_quotes(&h, ms);
		else if (!h.start_q && is_token(h.str[h.i]))
			handle_tokens(&h, ms);
		h.i++;
	}
	if (h.start_q)
		add_token_free(&h, ms);
	return (0);
}

int ft_token(t_myshell *ms)
{
	if (ms->exit_status != EXIT_SUCCESS)
		return (ms->exit_status);
	ms->exit_status = tokens2(ms);
	ms->exit_status = trim_quotes(ms);
	return (ms->exit_status);
}

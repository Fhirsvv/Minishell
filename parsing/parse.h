#ifndef PARSE_H
# define PARSE_H

# include <readline/history.h>
# include <readline/readline.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stddef.h>


typedef struct s_files
{
	char file_name[256];
	int	type_open;
	struct s_files *next;
}	t_files;

typedef struct s_com
{
	char **args;
	char *env_path;
	t_files *files;
	struct s_com *next;
}	t_com;

enum e_token_types
{
	PIPE,
	REDIR_D,
	DOBLE_REDIR_D,
	REDIR_I,
	HERE_DOC,
	WORD,
	D_QUOTE,
	S_QUOTE
};

typedef struct s_token
{
	char			*content;
	int				symbol;
	struct s_token	*next;
}	t_token;

typedef struct s_myshell
{
	char		**environ;
	char		*path;
	char		*prompt;
	int			error;
	int			exit_status;
	t_token		*tokens;
	t_com 		*t_com;
}	t_myshell;

typedef struct s_token_handler
{
	char		*str;
	char		*start_q;
	int			i;
	char		quote;
	t_myshell	*ms;
}	t_token_handler;


//MAIN.C
int				loop(t_myshell *tshell);
void			signals();
void			exit_minishell(t_myshell *ms);

//LIBFT
char			**ft_array_duplicate(char **arr);
void			*ft_calloc(size_t num, size_t size);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strtrim(char *s1, char const *set);
char			*ft_semi_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			free_arr(char **split_arr);

t_token			*ft_token_new(char *str, int type);
void			ft_tokenadd_after(t_token **lst, t_token *new, t_token *wh);
void			ft_tokenadd_back(t_token **lst, t_token *new);
void			ft_tokensubstitute(t_token **lst, t_token *new, t_token *wh);

size_t			ft_strlcpy(char *dest, const char *src, size_t size);

//TOKENIZER
int 			ft_token(t_myshell *ms);
int				tokens2(t_myshell *ms);
void			split_various_dolar(t_myshell *tshell);
int				add_token_free(t_token_handler *h, t_myshell *tshell);
void			update_last_token_symbol(t_myshell *tshell, int new_symbol);
void			ft_add_after(t_myshell *tshell, char **arr, t_token *new, int *i);
int				expander(t_myshell *tshell);
int 			ft_expander(t_myshell *ms);
int				token_type(char *str);
int				trim_quotes(t_myshell *ms);
int 			is_token(char c);

//COMANDS
int				ft_comand(t_myshell *ms);
char			**add_to_matrix(char **arr, char *new);
void			ft_copy(char *dst, char *src);
t_com 			*new_t_com();
int 			is_redir(t_token *t_next);
int 			is_word(t_token *t_next);

//UTILS - OTHERS
int 			parsing(t_myshell *tshell);
void			exit_minishell(t_myshell *ms);
char			*get_cmd_path(char *path, char *cmd);
char			*get_path(t_myshell *tshell);
int				count_quotes(const char *prompt);
int				count_quotes(const char *prompt);
int				how_many_finds(char *str, int c);
int				expander(t_myshell *tshell);

void			free_minishell(t_myshell *tshell);
int				ft_free(char *s);
void			ft_free2(char *arr1, char *arr2);
void			free_tokens(t_token **tk);
void 			free_tcoms(t_myshell *ms);

int				init(t_myshell *myshell, char **environ);
t_token_handler	init_token_handler(char *str, t_myshell *ms);
void			signals();

int				ft_path(t_myshell *ms);

#endif
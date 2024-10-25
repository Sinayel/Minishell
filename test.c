#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_data
{
	int				i;
	int				j;
	int				k;
	char			*value;
	char			**first_split;
	char			*input;
	int				type;
	char			**env;
	struct s_data	*next;
}					t_data;

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

void	print(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (data->first_split[i])
	{
		printf("%s -> ", data->first_split[i]);
		i++;
	}
	printf("NULL\n");
}

int	word_count_pipe(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '|' || str[i] == ' ' || str[i] == '\n'
				|| str[i] == '\t'))
		{
			if (str[i] == '|')
				wc++;
			i++;
		}
		if (str && str[i] != '\0')
			wc++;
		while (str[i] && (str[i] != '|' && str[i] != ' ' && str[i] != '\n'
				&& str[i] != '\t'))
			i++;
	}
	printf("wc = %d\n", wc);
	return (wc);
}

char **sortie(char **out, int i, int j, char *str, int k)
{
	out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
	if (!out[k])
	{
		while (k > 0)
			free(out[--k]);
		free(out);
		return (NULL);
	}
	strncpy(out[k], &str[j], i - j);
	out[k][i - j] = '\0';
	k++;
	return out;
}

char **for_pipe(char **out, int k)
{
	out[k] = (char *)malloc(sizeof(char) * 2);
	if (!out[k])
	{
		while (k > 0)
			free(out[--k]);
		free(out);
		return (NULL);
	}
	out[k][0] = '|';
	out[k][1] = '\0';
	return out;
}

int	first_verif(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
		i++;
	return i;
}

int	second_verif(char *str, int i)
{
	while (str[i] && (str[i] != ' ' && str[i] != '\n' && str[i] != '\t'
			&& str[i] != '|'))
		i++;
	return i;
}

char	**ft_split_pipe(char *str)
{
	t_data *data = get_data();
	char	**out;

	out = (char **)malloc(sizeof(char *) * (word_count_pipe(str) + 1));
	if (!out)
		return (NULL);
	while (str[data->i])
	{
		data->i = first_verif(str, data->i);
		if (str[data->i] == '|')
		{
			out = for_pipe(out, data->k);
			data->k++;
			data->i++;
		}
		data->j = data->i;
		data->i = second_verif(str, data->i);
		if (data->i > data->j)
		{
			out = sortie(out, data->i, data->j, str, data->k);
			data->k++;
		}
	}
	out[data->k] = NULL;
	init_var();
	return (out);
}

void init_var()
{
	t_data *data = get_data();
	data->i = 0;
	data->j = 0;
	data->k = 0;
}

int	main(void)
{
	t_data *data;

	data = get_data();
	init_var();
	while (1)
	{
		data->input = readline("Minishell> ");
		data->first_split = ft_split_pipe(data->input);
		if (!data->first_split)
			free(data->input);
		print();
		if (*data->input)
			add_history(data->input);
		free(data->input);
	}
	return (0);
}
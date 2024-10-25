#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_data
{
	char			*value;
	char			**first_split;
	char			*input;
    int             type;
	struct s_data	*next;
}					t_data;

//! UNIQUEMENT POUR LES STRUCTURE (NE MARCHE PAS AVEC LES LISTE CHAINEE)
t_data *get_data(void)
{
	static t_data data;
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

int	word_count(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
			i++;
		if (str && str[i] != '\0')
			wc++;
		while (str[i] && (str[i] != ' ' && str[i] != '\n' && str[i] != '\t'))
			i++;
	}
	return (wc);
}

char	**ft_split(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**out;

	i = 0;
	j = 0;
	k = 0;
	out = (char **)malloc(sizeof(char *) * (word_count(str) + 1));
	if (!out)
		return (NULL);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
			i++;
		j = i;
		while (str[i] && (str[i] != ' ' && str[i] != '\n' && str[i] != '\t'))
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			if (!out[k])
			{
				while (k > 0)
					free(out[--k]);
				free(out);
				return (NULL);
			}
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}

t_data	*add_last(t_data *list, char *value)
{
	t_data	*new_element;
	t_data	*temp;

	new_element = malloc(sizeof(t_data));
	if (!new_element)
		return (list);
	new_element->value = strdup(value);
    new_element->type = 0;
	new_element->next = NULL;
	if (list == NULL)
		return (new_element);
	temp = list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_element;
	return (list);
}

void	print_list(t_data *head)
{
	t_data	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%s -> ", temp->value);
		temp = temp->next;
	}
	printf("NULL\n");
}

void	ft_lstclear(t_data **lst)
{
	t_data	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->value); //1 Libere `value` du noeud actuel
		free(*lst);          //1 Libere le noeud actuel
		*lst = temp;
	}
	*lst = NULL;
}

t_data *init_list(t_data *list)
{
    t_data *data = get_data();
    int i = 0;
    while (data->first_split[i])
    {
        list = add_last(list, data->first_split[i]);
        i++;
    }
    return list;
}

int args(char *str)
{
    printf("str = %s\n", str);
    if(strcmp(str, "echo") == 0 ||      //3 Cmd a +1 d'arguments (ou 1 seul)
        strcmp(str, "cd") == 0 ||
        strcmp(str, "export") == 0 ||
        strcmp(str, "unset") == 0)
        return 0;
    else if(strcmp(str, "exit") == 0 || //3 Cmd a 1 arguments (Sans option)
            strcmp(str, "pwd") == 0 ||
            strcmp(str, "env") == 0)
        return 2;
    else
        return 1;
}

int check_cmd(t_data *list)
{
    t_data *temp = list;
    int i = 0;
    while(temp != NULL)
    {
        if(args(temp->value) == 1)
            return 1;
        temp = temp->next;
        i++;
    }
    return 0;
}

int	main(void)
{
	t_data	*list;
	t_data	*data;
    int i = 0;

	list = NULL;
	data = get_data();
	while (1)
	{
		data->input = readline("Minishell> ");
		data->first_split = ft_split(data->input);
        list = init_list(list);

        if (check_cmd(list) == 1)      //1 Check les arguments de base : Cd, pwd, exit...
            exit(1);

        print_list(list);
        printf("input = %s\n", data->input);
		ft_lstclear(&list);             //1 Libere tous les noeud de ma liste
		free(data->input);
	}
	return (0);
}

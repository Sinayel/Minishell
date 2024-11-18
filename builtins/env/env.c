/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:23:21 by judenis           #+#    #+#             */
/*   Updated: 2024/11/18 12:54:21 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// char	*get_env(const char *var, char **env)
// {
// 	int		i;
// 	size_t	len;

// 	i = 0;
// 	len = strlen(var);
// 	while (env[i])
// 	{
// 		if (strncmp(env[i], var, len) == 0 && env[i][len] == '=')
// 		{
// 			return (env[i] + len + 1);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// t_env *import_env(char **env)
// {
//     t_env	*new;
//     int		i;

//     i = 0;
//     new = NULL;
//     while (env[i])
//     {
        
//     }
//     return (new);
// }

// int main(int argc,char **argv, char **env)
// {
//     (void)argc;
//     (void)argv;
//     s_env *env = import_env(env);
    
//     return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strchr(const char *s, int c)
{
    int i;

    i = 0;
    while (s[i] != '\0' && s[i] != c)
        i++;    
    if (s[i] == c) 
        return (char*)&s[i];
    return NULL;
}

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*ptr;

	i = 0;
	len = ft_strlen(src);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// Fonction pour créer un nouveau nœud pour la liste chaînée
t_env *create_env_var(const char *name, const char *value)
{
    if (!name || !value)
        return NULL;
    t_env *new_node;
    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
    {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    new_node->name = ft_strdup(name);
    if (!new_node->name)
    {
        free(new_node);
        perror("Erreur strdup name");
        exit(EXIT_FAILURE);
    }
    new_node->value = ft_strdup(value);
    if (!new_node->value)
    {
        free(new_node->name);
        free(new_node);
        perror("Erreur strdup value");
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;
    return new_node;
}

// Fonction pour ajouter une variable d'environnement à la fin de la liste chaînée
void append_env_var(t_env **head, char *name, char *value)
{
    t_env *new_node;
    t_env *temp;
    
    new_node = create_env_var(name, value);
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Fonction pour afficher les variables d'environnement de la liste chaînée
void print_env_vars(t_env *head, char *name)
{
    t_env *temp = head;
    while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
            printf("%s=%s\n", temp->name, temp->value);
		}
		temp = temp->next;
	}
}

void print_env(t_env *head)
{
    t_env *temp;

    if (head == NULL)
        return;
    temp = head;
    while (temp != NULL)
	{
        printf("%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

char *return_env_value(t_env *head, char *name)
{
    t_env *temp;

    if (head == NULL)
        return (NULL);
    temp = head;
    while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
            return (temp->value);
		}
		temp = temp->next;
	}
    return (NULL);
}

// Fonction pour libérer la mémoire de la liste chaînée
void free_env_vars(t_env *head)
{
    t_env *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
}

// void	ft_lstaddback(t_list **alst, t_list *new)
// {
// 	t_list *ptr;

// 	if (alst && *alst)
// 	{
// 		ptr = *alst;
// 		while (ptr->next)
// 			ptr = ptr->next;
// 		ptr->next = new;
// 	}
// 	else if (alst)
// 		*alst = new;
// }

void env_create_oldpwd(t_env **env_list)
{
    t_env *new;
    char cwd[4096];

    getcwd(cwd, sizeof(cwd));
    new = (t_env *)malloc(sizeof(t_env));
    new->name = ft_strdup("OLDPWD");
    new->value = ft_strdup(cwd);
    new->next = NULL;
    (*env_list)->next = new;
}

void env_create_pwd(t_env **env_list)
{
    t_env *new;
    char cwd[4096];

    getcwd(cwd, sizeof(cwd));
    new = (t_env *)malloc(sizeof(t_env));
    new->name = ft_strdup("PWD");
    new->value = ft_strdup(cwd);
    new->next = NULL;
    *env_list = new;
}

void ft_free_env(t_env **lst)
{
    t_env *tmp;

    if (!lst || !*lst)
        return;

    while (*lst)
    {
        tmp = (*lst)->next;
        if ((*lst)->name)
            free((*lst)->name);
        if ((*lst)->value)
            free((*lst)->value);
        
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}

t_env *env_import(char **envp)
{
    t_env *env_list;
    char *env_entry;
    char *delimiter;
    char *name;
    int i;

    i = 0;
    env_list = NULL;
    if (!*envp)
    {
        env_create_pwd(&env_list);
        return (env_list);
    }
    while (envp[i])
    {
        env_entry = envp[i];
        delimiter = ft_strchr(env_entry, '=');

        if (delimiter != NULL)
        {
            *delimiter = '\0';
            name = env_entry;
            append_env_var(&env_list, name, delimiter + 1);
            *delimiter = '=';
            i++;
        }
    }
    return (env_list);
}

// int main(int argc, char **argv, char **envp)
// {
//     t_env *env = env_import(envp);
//     print_env_vars(env);
// }

// int main(int argc, char *argv[], char *envp[]) {
//     t_env *env_list = NULL;

//     // Parcours de envp pour extraire les variables d'environnement
//     int i;
//     i = 0;
//     while (envp[i]) {
//         char *env_entry = envp[i];
//         char *delimiter = ft_strchr(env_entry, '=');

//         if (delimiter != NULL) {
//             // Sépare le nom et la valeur de la variable d'environnement
//             *delimiter = '\0';
//             char *name = env_entry;
//             char *value = delimiter + 1;

//             // Ajout de la variable à la liste chaînée
//             append_env_var(&env_list, name, value);

//             // Rétablit le '=' dans envp[i] (pour ne pas altérer envp)
//             *delimiter = '=';
//             i++;
//         }
//     }

//     // Affichage des variables d'environnement
//     print_env_vars(env_list);

//     // Libération de la mémoire
//     free_env_vars(env_list);

//     return 0;
// }

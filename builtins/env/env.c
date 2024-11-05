/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:23:21 by judenis           #+#    #+#             */
/*   Updated: 2024/11/05 20:05:50 by judenis          ###   ########.fr       */
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

char *ft_strchr(const char *s, int c) {
    int i;
    i = 0;

    
    while (s[i] != '\0' && s[i] != c) {
        i++;
    }

    
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
    if (!name || !value) {
        return NULL;
    }

    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    new_node->name = ft_strdup(name);
    if (!new_node->name) {
        free(new_node);
        perror("Erreur strdup name");
        exit(EXIT_FAILURE);
    }

    new_node->value = ft_strdup(value);
    if (!new_node->value) {
        free(new_node->name);
        free(new_node);
        perror("Erreur strdup value");
        exit(EXIT_FAILURE);
    }

    new_node->next = NULL;
    return new_node;
}

// Fonction pour ajouter une variable d'environnement à la fin de la liste chaînée
void append_env_var(t_env **head, const char *name, const char *value) {
    t_env *new_node = create_env_var(name, value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        t_env *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Fonction pour afficher les variables d'environnement de la liste chaînée
void print_env_vars(t_env *head) {
    t_env *temp = head;
    while (temp != NULL) {
        printf("Name = %s Value = %s\n", temp->name, temp->value);
        temp = temp->next;
    }
}

// Fonction pour libérer la mémoire de la liste chaînée
void free_env_vars(t_env *head) {
    t_env *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
}

t_env *env_import(char **envp)
{
    
    t_env *env_list = NULL;

    // Parcours de envp pour extraire les variables d'environnement
    int i;
    i = 0;
    while (envp[i]) {
        char *env_entry = envp[i];
        char *delimiter = ft_strchr(env_entry, '=');

        if (delimiter != NULL) {
            // Sépare le nom et la valeur de la variable d'environnement
            *delimiter = '\0';
            char *name = env_entry;
            char *value = delimiter + 1;

            // Ajout de la variable à la liste chaînée
            append_env_var(&env_list, name, value);

            // Rétablit le '=' dans envp[i] (pour ne pas altérer envp)
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

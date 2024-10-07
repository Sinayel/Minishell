#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>

typedef struct {
    int some_value;
    char some_string[100];
} GlobalData;

char	**ft_split(char *str);
int	    word_count(char *str);
int	    ft_strcmp(const char *s1, const char *s2);
char	*ft_strncpy(char *s1, char *s2, int n);
int	    parsing(char *str[]);

#endif
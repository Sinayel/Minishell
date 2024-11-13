/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:09:45 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/13 13:29:36 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static size_t	ft_digitlen(long n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nbr;
	size_t	i;
	size_t	n_len;
	char	*str;

	nbr = (long)n;
	n_len = ft_digitlen(nbr);
	str = (char *)malloc(sizeof(char) * (n_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (n == 0)
		str[i] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		str[(n_len - 1) - i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[n_len] = 0;
	return (str);
}

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

char *get_pid(char *str)
{
    char *tmp = malloc(sizeof(char));
    char *pid = "1234";
    int i = 0;
    int j = 0;
    int len = ft_strlen(str);
    while(i < len)
    {
        if(str[i] == '$' && str[i + 1] == '$')
        {
            int k = 0;
            len += ft_strlen(pid);
            while(pid[k])
            {
                tmp[j] = pid[k];
                k++;
                j++;
            }
            i += 2;
        }
        else
            tmp[j++] = str[i++];
    }
    tmp[i] = '\0';
    return tmp;
}

int main(void)
{
    char *str = "Hello $$$World";
    char *tmp = get_pid(str);
    printf("str = %s\ntmp = %s\n", str, tmp);
    return 0;
}

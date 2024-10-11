/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:15:04 by judenis           #+#    #+#             */
/*   Updated: 2024/10/11 15:11:29 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    if (argc < 2)
    {
        printf("Pipex : infile <cmd1> <cmd2> outfile\n");
        return (1);
    }

    // Create a new array of arguments
    char **new_argv = &argv[1];

    // Execute the command
    execve(new_argv[0], new_argv, envp);

    // If execve returns, there was an error
    perror("execve");
    return (1);
}

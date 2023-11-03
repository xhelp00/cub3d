/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_other_choices(int choice, t_box *box)
{
	if (choice == 4)
	{
		printf("Exiting...\n");
		box->exit_menu = 1;
		exit(0);
	}
	else if (choice == 5)
	{
		if (box->music)
		{
			box->music = 0;
			printf("Music turned off.\n");
		}
		else if (!box->music)
		{
			box->music = 1;
			printf("Music turned on.\n");
		}
	}
	else
		printf("Invalid choice. Please enter a number between 1 and 5.\n");
}

void	process_choice(int choice, t_box *box)
{
	if (choice >= 1 && choice <= 3)
		set_map_filename(choice, box);
	else
		handle_other_choices(choice, box);
}

void	print_menu(void)
{
	printf("\n    ██████╗ ██╗   ██╗ ██████╗  ██████╗  ██████╗     \n");
	printf("   ██╔════╝ ██║   ██║ ██╔══██╗ ╚════██╗ ██╔══██╗     \n");
	printf("   ██║      ██║   ██║ ██████╔╝  █████╔╝ ██║  ██║     \n");
	printf("   ██║      ██║   ██║ ██╔══██╗  ╚═══██╗ ██║  ██║     \n");
	printf("   ╚██████╗ ╚██████╔╝ ██████╔╝ ██████╔╝ ██████╔╝     \n");
	printf("    ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝  ╚═════╝      \n");
	printf("                                                     \n");
	printf("    42 project presented by jbartosi & phelebra      \n");
	printf("                                                     \n");
	printf("      ██╗ ███████╗  █████╗   █████╗   ██████╗        \n");
	printf("      ██║ ██╔════╝ ██╔══██╗ ██╔══██╗ ██╔════╝        \n");
	printf("      ██║ ███████╗ ███████║ ███████║ ██║             \n");
	printf("      ██║ ╚════██║ ██╔══██║ ██╔══██║ ██║             \n");
	printf("      ██║ ███████║ ██║  ██║ ██║  ██║ ╚██████╗        \n");
	printf("      ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚═╝  ╚═╝  ╚═════╝   v1.42\n");
	printf("                                                     \n");
	printf("Terminal Menu:\n");
	printf("1. Choose map hell\n");
	printf("2. Choose map arena\n");
	printf("3. Choose map exampleTexture\n");
	printf("4. Exit\n");
	printf("5. Toggle Music On/Off\n");
	printf("Enter your choice (1-5): ");
}

void	get_user_input(t_box *box)
{
	int	choice;

	choice = 0;
	if (scanf("%d", &choice) != 1)
	{
		while (getchar() != '\n')
			continue ;
	}
	process_choice(choice, box);
}

void	menu(t_box *box)
{
	while (!box->map_filename && !box->exit_menu)
	{
		print_menu();
		get_user_input(box);
	}
}

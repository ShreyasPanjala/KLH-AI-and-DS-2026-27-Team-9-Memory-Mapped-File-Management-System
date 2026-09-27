#include <stdio.h>
#include <stdlib.h>

#include "syscall_demo.h"
#include "process_demo.h"
#include "ipc_demo.h"
#include "vm_demo.h"
#include "file_demo.h"
#include "thread_demo.h"

static void print_menu(void)
{
    printf("\n");
    printf("===============================================\n");
    printf("       LINUX MEMORY-MAPPED FILE SYSTEM\n");
    printf("          MANAGEMENT & TEST MODULE\n");
    printf("===============================================\n");
    printf("1. System Call Operations\n");
    printf("2. Process Management\n");
    printf("3. Inter-Process Communication\n");
    printf("4. Memory Mapping\n");
    printf("5. File Operations\n");
    printf("6. Concurrent Access\n");
    printf("7. Run Complete System Test\n");
    printf("0. Exit\n");
    printf("===============================================\n");
    printf("Enter choice: ");
}

static void run_choice(int choice)
{
    switch (choice)
    {
        case 1:
            run_syscall_demo();
            break;

        case 2:
            run_process_demo();
            break;

        case 3:
            run_ipc_demo();
            break;

        case 4:
            run_vm_demo();
            break;

        case 5:
            run_file_demo();
            break;

        case 6:
            run_thread_demo();
            break;

        case 7:
            run_syscall_demo();
            run_process_demo();
            run_ipc_demo();
            run_vm_demo();
            run_file_demo();
            run_thread_demo();

            printf("\n");
            printf("===============================================\n");
            printf("       ALL SYSTEM TESTS COMPLETED\n");
            printf("===============================================\n");
            break;

        default:
            printf("Invalid choice.\n");
    }
}

int main(int argc, char *argv[])
{
    /*
     * GUI mode:
     * ./os_demo 1
     * ./os_demo 2
     * ...
     * ./os_demo 7
     */
    if (argc == 2)
    {
        int choice = atoi(argv[1]);

        if (choice >= 1 && choice <= 7)
        {
            run_choice(choice);
            return 0;
        }

        printf("Invalid command-line option.\n");
        return 1;
    }

    /*
     * Normal terminal mode
     */
    int choice;

    printf("\n");
    printf("===============================================\n");
    printf("       LINUX MEMORY-MAPPED FILE SYSTEM\n");
    printf("          MANAGEMENT & TEST MODULE\n");
    printf("===============================================\n");

    while (1)
    {
        print_menu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            continue;
        }

        if (choice == 0)
        {
            printf("\nExiting system.\n");
            break;
        }

        run_choice(choice);
    }

    return 0;
}

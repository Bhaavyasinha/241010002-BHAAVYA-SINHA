#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LEN 100
char *filename = "tasks.txt";

typedef struct {
    char task[MAX_LEN];
} Todo;

Todo tasks[MAX_TASKS];
int taskCount = 0;



void loadTasks() {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return;
    while (fgets(tasks[taskCount].task, MAX_LEN, file)) {
        tasks[taskCount].task[strcspn(tasks[taskCount].task, "\n")] = '\0';
        taskCount++;
    }
    fclose(file);
}



void saveTasks() {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s\n", tasks[i].task);
    }
    fclose(file);
}



void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task limit reached!\n");
        return;
    }
    printf("Enter new task: ");
    getchar(); 
    fgets(tasks[taskCount].task, MAX_LEN, stdin);
    tasks[taskCount].task[strcspn(tasks[taskCount].task, "\n")] = '\0';
    taskCount++;
    printf("Task added!\n");
}



void viewTasks() {
    if (taskCount == 0) {
        printf("No tasks found.\n");
        return;
    }
    printf("\n--- To-Do List ---\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s\n", i + 1, tasks[i].task);
    }
    printf("------------------\n");
}



void deleteTask() {
    int del;
    viewTasks();
    if (taskCount == 0) return;
    printf("Enter task number to delete: ");
    scanf("%d", &del);
    if (del < 1 || del > taskCount) {
        printf("Invalid task number!\n");
        return;
    }
    for (int i = del - 1; i < taskCount - 1; i++) {
        strcpy(tasks[i].task, tasks[i + 1].task);
    }
    taskCount--;
    printf("Task deleted!\n");
}



int main() {
    int choice;
    loadTasks();

    do {
        printf("\n--- TO-DO LIST MENU ---\n");
        printf("1. Add Task\n2. View Tasks\n3. Delete Task\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: deleteTask(); break;
            case 4: saveTasks(); printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "functions.h"

int main() {

    t_db *database;
    char *command = (char *)malloc(MAX_CMD_LEN * sizeof(char));
    size_t size = MAX_CMD_LEN;
    while (1)
    {
        getline(&command, &size, stdin);
        if(command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }
        char *buffer = (char *)calloc(MAX_CMD_LEN, sizeof(char));
        strcpy(buffer, command);
        char *token = strtok(buffer, " ");

        if(!strcmp(token, "INIT_DB")) {
            char *database_name = strtok(NULL, " ");
            database = INIT_DB(database_name);
        } else if(!strcmp(token, "DELETE_DB")) {
            DELETE_DB(database);
            free(buffer);
            free(command);
            exit(0);
        } else if(!strcmp(token, "CREATE")) {
            char *table_name = strtok(NULL, " ");
            if(find_table(database, table_name)) {
                printf("Table \"%s\" already exists.\n", table_name);
            } else {
                char *args = buffer + strlen(token) + strlen(table_name) + 2;
                if(*args == '\0') {
                    args = NULL;
                }
                CREATE(database, table_name, args);
            }
        } else if(!strcmp(token, "DELETE")) {
            char *table_name = strtok(NULL, " ");
            if(find_table(database, table_name)) {
                char *args = buffer + strlen(token) + strlen(table_name) + 2;
                if(*args == '\0') {
                    args = NULL;
                }
                DELETE(database, table_name, args);
            } else {
                printf("Table \"%s\" not found in database.\n", table_name);
            }
        } else if(!strcmp(token, "PRINT_DB")) {
            PRINT_DB(database);
        } else if(!strcmp(token, "PRINT")) {
            char *table_name = strtok(NULL, " ");
            if(find_table(database, table_name)) {
                PRINT(find_table(database, table_name), "header");
                PRINT(find_table(database, table_name), "content");
            } else {
                printf("Table \"%s\" not found in database.\n", table_name);
            }
        } else if(!strcmp(token, "SEARCH")) {
            char *table_name = strtok(NULL, " ");
            if(find_table(database, table_name)) {
                char *args = buffer + strlen(token) + strlen(table_name) + 2;
                if(*args == '\0') {
                    args = NULL;
                }
                SEARCH(find_table(database, table_name), args);
            } else {
                printf("Table \"%s\" not found in database.\n", table_name);
            }
        } else if(!strcmp(token, "ADD")) {
            char *table_name = strtok(NULL, " ");
            if(find_table(database, table_name)) {
                char *args = buffer + strlen(token) + strlen(table_name) + 2;
                if(*args == '\0') {
                    args = NULL;
                }
                ADD(find_table(database, table_name), args);
            } else {
                printf("Table \"%s\" not found in database.\n", table_name);
            }
        } else if(!strcmp(token, "CLEAR")) {
            char *table_name = strtok(NULL, " ");
            if(find_table(database, table_name)) {
                CLEAR(find_table(database, table_name));
            } else {
                printf("Table \"%s\" not found in database.\n", table_name);
            }
        } else {
            printf("Unknown command: \"%s\"\n", command);
        }
        free(buffer);
    }
    return 0;
}
#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h> //access
#include <string.h>


//#define _POSIX_C_SOURCE >= 200809L

int main(void)
{
    char* dbname = NULL;
    char* timestamp = NULL;
    size_t line_length = 0;
    sqlite3* db = NULL;
    int user = -1;
    int spent = -1;

    if(getline(&dbname, &line_length, stdin) == -1) {
        fprintf(stderr, "Incorrent arguments supplied!");
        return 1;
    }

    dbname[strlen(dbname)-1] = '\0';

    if(access(dbname, F_OK) != -1) {
        if(sqlite3_open(dbname, &db) != SQLITE_OK) {
            fprintf(stderr, "Error while opening database");
            return 2;
        }
    } else {
        if(sqlite3_open(dbname, &db)!= SQLITE_OK) {
            fprintf(stderr, "Error while creating database");
            return 3;
        }
    }

    if(scanf("%d\n", &user) <= 0 || getline(&timestamp, &line_length, stdin) == -1 ||  scanf("%d", &spent) <= 0) {
        fprintf(stderr, "Incorrent arguments supplied!");
        return 1;
    }

    timestamp[strlen(timestamp)-1] = '\0';









    return 0;
}


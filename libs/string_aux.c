#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "memory.h"
#include "string_aux.h"

void strcut(char *buffer, const char *string, int min, int max)
{
    int counter = 0;
    for (int i = min; i <= max; i++)
    {
        buffer[counter] = string[i];
        counter++;
    }
    buffer[counter] = '\0';
}

int array_has_string(const char **array, int size, const char *string)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(array[i], string) == 0)
        {
            return i;
        }
    }

    return -1;
}

void strtolower(char *string)
{
    for (size_t i = 0; i < strlen(string); i++)
    {
        string[i] = tolower(string[i]);
    }
}

int add_to_queue(char **queue, int *queue_counter, char *string)
{
    if (*queue_counter + 1 > MAX_QUEUE)
    {
        errno = ENOBUFS;
        return -1;
    }
    else
    {
        strcpy(queue[*queue_counter], string);
        (*queue_counter)++;
    }
    return 0;
}

void clean_queue(char **queue)
{
    for (int i = 0; i < MAX_QUEUE; i++)
    {
        for (int j = 0; j < MAX_STRING_SIZE; j++)
        {
            queue[i][j] = '\0';
        }
    }
}

char **queue_new()
{
    int quantity = MAX_QUEUE;
    int length = MAX_STRING_SIZE;

    char *matrix = MALLOC(sizeof(char) * quantity * length);

    char **matrix_aux = (char **)MALLOC(sizeof(char *) * quantity);

    for (int i = 0; i < quantity; i++)
    {
        matrix_aux[i] = &(matrix[i * length]);
    }

    return matrix_aux;
}

void queue_free(char **queue)
{
    FREE(*queue); // FREE(matrix[0])
    FREE(queue);
}
#ifndef _STRING_AUX_H_
#define _STRING_AUX_H_

#ifndef MAX_QUEUE
#define MAX_QUEUE 100
#endif

#ifndef MAX_STRING_SIZE
#define MAX_STRING_SIZE 256
#endif

/**
 * @brief Cuts a string between two positions
 *
 * @param buffer
 * @param string
 * @param min
 * @param max
 */
void strcut(char *buffer, const char *string, int min, int max);

/**
 * @brief Search the occurence in the array returning its position (-1 if not found)
 *
 * @param array
 * @param size
 * @param string
 * @return int
 */
int array_has_string(const char **array, int size, const char *string);

/**
 * @brief Switches all the upper case characters in a string to its matching lower case
 *
 * @param string
 */
void strtolower(char *string);

/**
 * @brief Add to queue helper
 *
 * @param files_queue
 * @param queue_counter
 * @param string
 * @return 0 - ok | -1 error and errno set
 */
int add_to_queue(char **files_queue, int *queue_counter, char *string);

/**
 * @brief Cleans queue
 *
 * @param queue
 */
void clean_queue(char **queue);

/**
 * @brief Creates a new queue in heap
 *
 * @return char**
 */
char **queue_new();

/**
 * @brief Frees queue memory
 *
 * @param queue
 */
void queue_free(char **queue);

#endif
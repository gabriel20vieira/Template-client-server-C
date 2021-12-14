/**
 * @file: server.c
 * @date: 14-12-2021
 * @author: author
 */
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "../libs/memory.h"
#include "../libs/debug.h"
#include "../common/common.h"
#include "../gengetopt/server_opt.h"
#include "../libs/inet_aux.h"
#include "../libs/binary_aux.h"

int main(int argc, char *argv[])
{
    struct gengetopt_args_info args_info;

    if (cmdline_parser(argc, argv, &args_info) != 0)
    {
        exit(ERR_ARGS);
    }

    /*
     * Code
     */
    DEBUG("Not implemented");

    cmdline_parser_free(&args_info);

    return 0;
}

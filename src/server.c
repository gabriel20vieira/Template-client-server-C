/**
 * @file: server.c
 * @date: 2016-11-17
 * @author: autor
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

int main(int argc, char *argv[])
{
    /* Estrutura gerada pelo utilitario gengetopt */
    struct gengetopt_args_info args_info;

    /* Processa os parametros da linha de comando */
    if (cmdline_parser(argc, argv, &args_info) != 0)
    {
        exit(ERR_ARGS);
    }

    /*
     * Inserir codigo do servidor
     */
    DEBUG("Código");

    cmdline_parser_free(&args_info);

    return 0;
}

/*
 *  ____  ______  __   ____ _     ___
 * |  _ \|  _ \ \/ /  / ___| |   |_ _|
 * | | | | |_) \  /  | |   | |    | |
 * | |_| |  __//  \  | |___| |___ | |
 * |____/|_|  /_/\_\  \____|_____|___|
 * 
 * Author: Erfan Mola
 * Developix Inc
 * 
 */

#include <getopt.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <regex.h>

#define PROGNAME "dpxcli"
#define DPXAPI   "https://dpx.developix.ir/api"

#include "modules/utils.c"

#include "modules/balance.c"
#include "modules/help.c"
#include "modules/revoke.c"
#include "modules/transaction.c"
#include "modules/transactions.c"
#include "modules/transfer.c"
#include "modules/verify.c"

int main(int argc, char *argv[]) {

    if (argc > 1) {

        char *command       = argv[1];
        char *command_param = argv[2];
        
        int opt;

        char *wallet      = NULL;
        char *secret      = NULL;
        char *destination = NULL;
        char *id          = NULL;
        char *offset      = NULL;
        char *amount      = NULL;

        struct option long_options[] = {
            {"wallet",      required_argument, NULL, 'w'},
            {"secret",      required_argument, NULL, 's'},
            {"destination", required_argument, NULL, 'd'},
            {"id",          required_argument, NULL, 'i'},
            {"offset",      required_argument, NULL, 'o'},
            {NULL, 0, NULL, 0}
        };

        while ((opt = getopt_long(argc, argv, "w:s:d:i:o:a:", long_options, NULL)) != -1) {

            switch (opt) {

                case 'w':
                case 0:
                    wallet = optarg;
                    break;
                    
                case 's':
                case 1:
                    secret = optarg;
                    break;

                case 'd':
                case 2:
                    destination = optarg;
                    break;

                case 'i':
                case 3:
                    id = optarg;
                    break;

                case 'o':
                case 4:
                    offset = optarg;
                    break;

                case 'a':
                case 5:
                    amount = optarg;
                    break;

                default:
                    break;

            }

        }

        if (strcmp(command, "balance") == 0) {

            if (wallet == NULL || (command_param != NULL && strcmp(command_param, "help") == 0) || secret != NULL || destination != NULL || id != NULL || offset != NULL || amount != NULL) {

                fprintf(stderr, "\033[36m\033[1mUsage:\033[0m\033[0m " PROGNAME " %s -w|--wallet <wallet>\n", command);

            }else if (!(is_md5(wallet))) {

                fprintf(stderr, "\033[31mError:\033[0m \033[1mInvalid wallet structure\033[0m\n");

            }else{

                show_balance(wallet);

            }

        }else if (strcmp(command, "help") == 0) {

            show_help();

        }else if (strcmp(command, "revoke") == 0) {

            if (wallet == NULL || secret == NULL || (command_param != NULL && strcmp(command_param, "help") == 0) || destination != NULL || id != NULL || offset != NULL || amount != NULL) {

                fprintf(stderr, "\033[36m\033[1mUsage:\033[0m\033[0m " PROGNAME " %s -w|--wallet <wallet> -s|--secret <secret>\n", command);

            }else if (!(is_md5(wallet)) || !(is_md5(secret))) {

                if (!(is_md5(wallet))) {
                    
                    fprintf(stderr, "\033[31mError:\033[0m \033[1mInvalid wallet structure\033[0m\n");

                }else if (!(is_md5(secret))) {

                    fprintf(stderr, "\033[31mError:\033[0m \033[1mInvalid secret structure\033[0m\n");

                }

            }else{

                show_revoke(wallet, secret);

            }

        }else if (strcmp(command, "transaction") == 0) {

            if (id == NULL || (command_param != NULL && strcmp(command_param, "help") == 0) || secret != NULL || destination != NULL || wallet != NULL || offset != NULL || amount != NULL) {

                fprintf(stderr, "\033[36m\033[1mUsage:\033[0m\033[0m " PROGNAME " %s -i|--id <transactionId>\n", command);

            }else if (!(is_md5(id))) {

                fprintf(stderr, "\033[31mError:\033[0m \033[1mInvalid transactionId structure\033[0m\n");

            }else{

                show_transaction(id);

            }

        }else if (strcmp(command, "transactions") == 0) {

            if (offset != NULL && (atoi(offset) < 0)) {

                fprintf(stderr, 
                    "\033[31mError:\033[0m \033[1mInvalid offset structure\033[0m\n"
                    "\033[36m\033[1mUsage:\033[0m\033[0m " PROGNAME " %s (-o|--offset <offset>)? (-w|--wallet <departure>)? (-d|--destination <destination>)?\n",
                    command
                );

            }else if (wallet != NULL && !(is_md5(wallet))) {

                fprintf(stderr, 
                    "\033[31mError:\033[0m \033[1mInvalid departure structure\033[0m\n"
                    "\033[36m\033[1mUsage:\033[0m\033[0m " PROGNAME " %s (-o|--offset <offset>)? (-w|--wallet <departure>)? (-d|--destination <destination>)?\n",
                    command
                );

            }else if (destination != NULL && !(is_md5(destination))) {

                fprintf(stderr, 
                    "\033[31mError:\033[0m \033[1mInvalid destination structure\033[0m\n"
                    "\033[36m\033[1mUsage:\033[0m\033[0m " PROGNAME " %s (-o|--offset <offset>)? (-w|--wallet <departure>)? (-d|--destination <destination>)?\n",
                    command
                );

            }else if ((command_param != NULL && strcmp(command_param, "help") == 0) || secret != NULL || id != NULL || amount != NULL) {

                fprintf(stderr,
                    "\033[36m\033[1mUsage:\033[0m\033[0m " PROGNAME " %s (-o|--offset <offset>)? (-w|--wallet <departure>)? (-d|--destination <destination>)?\n",
                    command
                );

            }else{

                show_transactions(offset, wallet, destination);

            }

        }else if (strcmp(command, "transfer") == 0) {

            if (wallet == NULL || secret == NULL || destination == NULL || amount == NULL || (command_param != NULL && strcmp(command_param, "help") == 0) || id != NULL || offset != NULL) {

                fprintf(stderr, "\033[36m\033[1mUsage:\033[0m\033[0m " PROGNAME " %s -a|--amount <amount> -w|--wallet <wallet> -s|--secret <secret> -d|--destination <destination>\n", command);

            }else if (!(is_md5(wallet)) || !(is_md5(secret)) || !(is_md5(destination))) {

                if (!(is_md5(wallet))) {
                    
                    fprintf(stderr, "\033[31mError:\033[0m \033[1mInvalid wallet structure\033[0m\n");

                }else if (!(is_md5(secret))) {

                    fprintf(stderr, "\033[31mError:\033[0m \033[1mInvalid secret structure\033[0m\n");

                }else if (!(is_md5(destination))) {

                    fprintf(stderr, "\033[31mError:\033[0m \033[1mInvalid destination structure\033[0m\n");

                }

            }else{

                if (atof(amount) > 0) {

                    show_transfer(wallet, secret, destination, amount);

                }else{

                    fprintf(stderr, "\033[31mError:\033[0m \033[1mInvalid Amount\033[0m\n");

                }

            }

        }else if (strcmp(command, "verify") == 0) {

            if (wallet == NULL || secret == NULL || (command_param != NULL && strcmp(command_param, "help") == 0) || destination != NULL || id != NULL || offset != NULL || amount != NULL) {

                fprintf(stderr, "\033[36m\033[1mUsage:\033[0m\033[0m " PROGNAME " %s -w|--wallet <wallet> -s|--secret <secret>\n", command);

            }else if (!(is_md5(wallet)) || !(is_md5(secret))) {

                if (!(is_md5(wallet))) {
                    
                    fprintf(stderr, "\033[31mError:\033[0m \033[1mInvalid wallet structure\033[0m\n");

                }else if (!(is_md5(secret))) {

                    fprintf(stderr, "\033[31mError:\033[0m \033[1mInvalid secret structure\033[0m\n");

                }

            }else{

                show_verify(wallet, secret);

            }

        }else{

            show_help();

        }
    
    }else{

        show_help();

    }

    return 0;

}
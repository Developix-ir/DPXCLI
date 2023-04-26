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

static void show_transaction(char* transactionId) {

    char endpoint[128] = "/transaction/";

    strcat(endpoint, transactionId);

    char* result = dpx_request_get(endpoint);

    if (result != NULL) {

        json_object *result_json = json_tokener_parse(result);

        if (strcmp(json_object_get_string(json_object_object_get(result_json, "status")), "success") == 0) {

            json_object *transaction = json_tokener_parse(json_object_get_string(json_object_object_get(result_json, "result")));

            fprintf(stdout,
                "╔═════════════════════════════════════════════════╗\n"
                "║ \033[36m\033[1mTransaction Information                         \033[0m\033[0m║\n"
                "║                                                 ║\n"
                "║ \033[36m\033[1mTransactionID:\033[0m %s\033[0m ║\n"
                "║ \033[36m\033[1mDeparture:    \033[0m %s\033[0m ║\n"
                "║ \033[36m\033[1mDestination:  \033[0m %s\033[0m ║\n"
                "║ \033[36m\033[1mAmount:       \033[0m %s\033[0m ║\n"
                "║ \033[36m\033[1mFee:          \033[0m %s\033[0m ║\n"
                "║ \033[36m\033[1mTimestamp:    \033[0m %s\033[0m ║\n"
                "╚═════════════════════════════════════════════════╝\n",
                pad_string(json_object_get_string(json_object_object_get(transaction, "transaction")), 32),
                pad_string(json_object_get_string(json_object_object_get(transaction, "departure")), 32),
                pad_string(json_object_get_string(json_object_object_get(transaction, "destination")), 32),
                pad_string(json_object_get_string(json_object_object_get(transaction, "amount")), 32),
                pad_string(json_object_get_string(json_object_object_get(transaction, "fee")), 32),
                pad_string(json_object_get_string(json_object_object_get(transaction, "timestamp")), 32)
            );

        }else{

            fprintf(stderr, 
                "\033[31mError Code:\033[0m \033[1m%s\033[0m\n"
                "\033[31mError Info:\033[0m \033[1m%s\033[0m\n",
                json_object_get_string(json_object_object_get(result_json, "error")),
                json_object_get_string(json_object_object_get(result_json, "info"))
            );

        }

        json_object_put(result_json);

    }else{

        fprintf(stderr, "Invalid response\n");

    }

    free(result);

}

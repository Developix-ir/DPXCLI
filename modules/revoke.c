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

static void show_revoke(char* wallet, char* secret) {

    postField pd[2] = {
        { "wallet", wallet },
        { "secret", secret },
    };

    char* result = dpx_request_post("/revoke", pd, (sizeof(pd) / sizeof(postField)));

    if (result != NULL) {

        json_object *result_json = json_tokener_parse(result);

        if (strcmp(json_object_get_string(json_object_object_get(result_json, "status")), "success") == 0) {

            fprintf(stdout, "\033[36mSecret has been revoked, the new Secret is: \033[1m%s\033[0m\033[0m\n", json_object_get_string(json_object_object_get(result_json, "result")));

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

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

static void show_help(void) {

    fprintf(stderr, "\033[36m\033[1mUsage:\033[0m\033[0m " PROGNAME " [command] [options]\n\n"
        "\033[36m\033[1mbalance     \033[0m\033[0m - retrieves the balance of the wallet\n"
        "\033[36m\033[1mhelp        \033[0m\033[0m - shows this help menu\n"
        "\033[36m\033[1mrevoke      \033[0m\033[0m - revokes the secret of the wallet\n"
        "\033[36m\033[1mtransaction \033[0m\033[0m - retrieves information of the given transaction id\n"
        "\033[36m\033[1mtransactions\033[0m\033[0m - retrieves transactions in descending order from specified offset (default is 0)\n"
        "\033[36m\033[1mtransfer    \033[0m\033[0m - transfers specified amount of DPX from departure wallet to destination wallet\n"
        "\033[36m\033[1mverify      \033[0m\033[0m - verifies a wallet credentials\n"
    );

}

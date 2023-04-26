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

#include "utils.h"

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    
    char *response = (char *) userdata;
    
    size_t response_size = strlen(response);
    size_t data_size = size * nmemb;
    
    memcpy(response + response_size, ptr, data_size);
    
    response[response_size + data_size] = '\0';
    
    return data_size;

}

char* dpx_request_post(char endpoint[], postField pd[], size_t postFieldsCount) {

    char response[40960] = {0};

    CURL *curl;
    CURLcode res;
    curl_mime *formData = NULL;
    curl_mimepart *field = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl) {

        char url[256];

        strcpy(url, DPXAPI);
        strcat(url, endpoint);

        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        

        formData = curl_mime_init(curl);

        for (int i = 0; i < postFieldsCount; i++) {

            field = curl_mime_addpart(formData);

            curl_mime_name(field, pd[i].key);
            curl_mime_data(field, pd[i].value, CURL_ZERO_TERMINATED);

        }

        curl_easy_setopt(curl, CURLOPT_MIMEPOST, formData);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
         
            fprintf(stderr, "operation failed: %s\n", curl_easy_strerror(res));
            return NULL;

        }

        curl_easy_cleanup(curl);
        curl_mime_free(formData);

    }

    curl_global_cleanup();

    if (response) {
    
        json_object* json_obj = json_tokener_parse(response);

        if (json_obj == NULL) {

            return NULL;

        }

        json_object_put(json_obj);

    }

    char* response_ptr = malloc(40960);
    strcpy(response_ptr, response);
    
    return response_ptr;

}

char* dpx_request_get(char endpoint[]) {

    char response[40960] = {0};

    CURL *curl;
    CURLcode res;
    curl_mime *formData = NULL;
    curl_mimepart *field = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if (curl) {

        char url[512];

        strcpy(url, DPXAPI);
        strcat(url, endpoint);

        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {

            fprintf(stderr, "operation failed: %s\n", curl_easy_strerror(res));
            return NULL;

        }

        curl_easy_cleanup(curl);
        curl_mime_free(formData);

    }

    curl_global_cleanup();

    if (response) {
    
        json_object* json_obj = json_tokener_parse(response);

        if (json_obj == NULL) {

            return NULL;

        }

        json_object_put(json_obj);

    }

    char* response_ptr = malloc(40960);
    strcpy(response_ptr, response); 
    
    return response_ptr;

}

int is_md5(char *str) {

    regex_t regex;
    int reti;

    char *pattern = "^[a-f0-9]{32}$";

    reti = regcomp(&regex, pattern, REG_EXTENDED);

    if (reti) {
        return 0;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;

}

const char* pad_string(const char* str, int padded_length) {

    int str_length = strlen(str);
    
    if (padded_length <= str_length) {

        return str;

    }
    
    char* padded_str = (char*) malloc(padded_length + 1);
    
    if (padded_str == NULL) {

        return NULL;

    }
    
    strncpy(padded_str, str, str_length);
    padded_str[str_length] = '\0';
    
    if (str_length < padded_length) {

        memset(padded_str + str_length, ' ', padded_length - str_length);
        padded_str[padded_length] = '\0';

    }
    
    return padded_str;

}
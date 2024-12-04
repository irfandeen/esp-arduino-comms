#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

int main(void) {
    CURL *curl;
    CURLcode res;

    do {
        printf("Enter 1/2/3 to on/off/blink the LED on the remote ESP32 respectively\
        (anything else to exit): ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid Input\n");
            return 1;
        };
        curl = curl_easy_init();
        if (curl) {
            char req_buff[100] = "http://192.168.68.55";
            
            if (choice == 1) strcat(req_buff, "/on"); 
            else if (choice == 2) strcat(req_buff, "/off"); 
            else if (choice == 3) strcat(req_buff, "/blink"); 
            else break;

            printf("Requesting %s\n", req_buff);

            curl_easy_setopt(curl, CURLOPT_URL, req_buff);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
    } while(1);

    return 0;
}

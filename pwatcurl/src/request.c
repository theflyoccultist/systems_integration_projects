#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>

void perform_get_request(const char *url) {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "[pwatcurl][error] '%s'\n", curl_easy_strerror(res));
    } else {
      printf("[pwatcurl] GET request succeded. Mood: tolerable.\n");
    }

    curl_easy_cleanup(curl);
  } else {
    fprintf(
        stderr,
        "[pwatcurl][fatal] Could not initialize curl. Feeling: dramatic.\n");
  }
}

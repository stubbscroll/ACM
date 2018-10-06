/* solution for raw data, hard input. must be run 3 times. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <curl/easy.h>

CURL *curl;

void setcookie() {
	CURLcode res;
	curl_easy_setopt(curl,CURLOPT_COOKIEFILE,"");
	res=curl_easy_setopt(curl,CURLOPT_COOKIE,
		"ipsc2018ann=3; "
		"ipscsessid=4aa265d793766cac1544ee139a6f1c8f8a325690; ");
	if(res!=CURLE_OK) puts("inserting cookie failed");
}

void submitPOST() {
	static char s[100];
	sprintf(s,"hallo");
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl=curl_easy_init();
	if(curl) {
		setcookie();
		curl_easy_setopt(curl,CURLOPT_URL,"https://ipsc.ksp.sk/2018/practice/problems/r2");
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,s);
		res=curl_easy_perform(curl);
		if(CURLE_OK!=res) printf("failed post %s\n",curl_easy_strerror(res)),exit(1);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

int main() {
	submitPOST();
	return 0;
}

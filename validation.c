#include <ctype.h>
#include <string.h>

int is_valid_order(const char *text){
	if(strcmp(text, "") == 0){
		return 0;
	}
	
	if(strcmp(text, "0") == 0){
		return 0;
	}
	
	int valid = 1;
	int len = strlen(text);
	for(int i = 0; i < len; i++){ 
		if(!isdigit(text[i])){
			valid = 0;
		}
	}
	
	return valid;
}

int is_valid_coefficient(const char *text){
	if(strcmp(text, "") == 0){
		return 0;
	}
	
	int valid = 1;
	int len = strlen(text);
	if(len >= 1){ /* Avoid segfault */
		if(!isdigit(text[0]) && text[0] != '-'){
			valid = 0;
		}
	}
	
	for(int i = 1; i < len; i++){ 
		if(!isdigit(text[i]) && text[i] != '.'){
			valid = 0;
		}
	}
	
	return valid;
}


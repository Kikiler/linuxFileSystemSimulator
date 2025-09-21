#include "linkedList.h"
#include <assert.h>

int main(void){
	//STRING LITERALS ARE IMMUTABLE YOU PIG
linkedList* list = fromStrToList("/Applications/Android Studio.app/Contents/license/commons-io-2.4.jar-NOTICE/");
printList(list);
destroy(list);
//assert(list == NULL);
}

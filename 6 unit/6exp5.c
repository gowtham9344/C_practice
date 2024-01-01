#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist{
	struct nlist *next;
	char* name;
	char* defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s){
	unsigned hashval;
	
	for(hashval = 0; *s != '\0'; s++){
		hashval = *s + 31 * hashval;	
	}

	return hashval % HASHSIZE;
}

struct nlist *lookup(char* s){
	struct nlist *np;

	for(np = hashtab[hash(s)]; np != NULL; np = np->next)
		if(strcmp(s,np->name) == 0)
			return np;
	return NULL;
}

struct nlist *install(char *name,char* defn){
	struct nlist *np;
	unsigned hashval;

	if( (np = lookup(name)) == NULL){
		np = (struct nlist *) malloc(sizeof(*np));
		if(np == NULL || (np->name = strdup(name)) == NULL){
			return NULL;
		}
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;	
	}
	else{
		free((void*) np->defn);
	}
	if((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

void undef(char* name){
	struct nlist *np = NULL;
	struct nlist *prev = NULL;

	for(np = hashtab[hash(name)]; np != NULL; np = np->next){
		if(strcmp(name,np->name) == 0)
			break;
		prev = np;
	}
	if(np != NULL){
		if(prev == NULL){
			hashtab[hash(name)] = np -> next;	
		}
		else{
			prev->next = np->next;	
		}
		free(np->name);
		free(np->defn);
		free(np);
	}
		
}

int main(){
	install("hello","1");
	install("world","2");
	install("king","3");
	printf("value of hello is %s\n",lookup("hello")->defn);
	printf("value of world is %s\n",lookup("world")->defn);
	printf("value of king is %s\n",lookup("king")->defn);

	undef("hello");
	printf("memory location of hello is %s\n",lookup("hello"));
}

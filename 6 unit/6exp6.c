#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define HASHSIZE 101
#define SIZE 100000

int bufp = 0;
int buf[SIZE];


struct nlist{
	struct nlist *next;
	char* name;
	char* defn;
};

static struct nlist *hashtab[HASHSIZE];

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= SIZE){
		printf("Maximum size exceeded\n");
	}
	else{
		buf[bufp++] = c;
	}
}

unsigned hash(char *s){
	unsigned hashval;
	
	for(hashval = 0; *s != '\0'; s++){
		hashval = *s + 31 * hashval;	
	}

	return hashval % HASHSIZE;
}

int getword(char* word,int lim){ 
	int c;
	char *w = word;
	
	while((c = getch()) == ' ' || c == '\t')
		;

	if(c == '\n'){
		word[0] = '\n';
		word[1] = '\0';
		return '\n';	
	}
	else if(c == '#'){
		word[0] = '#';
		word[1] = '\0';
		return '#';	
	}

	if(isalnum(c) || c == '_'){
		*w++ = c;
		for(;--lim > 0 ;w++){
			if(!isalnum(*w = getch()) && *w != '_'){
				ungetch(*w);
				break;		
			}	
		}
	}
	else if(!isalpha(c)){
		if( c == '\"'){
			for(c = getch();c!='\"'; c = getch());		
		}
		else if(c == '/'){
			if((c = getch()) == '/'){
				for(c = getch();c!='\n'; c = getch());
			}
			else if(c == '*'){
				int t;
				for(c = getch(),t = getch(); c != '*' && t!='/';c = getch(),t = getch()){
					ungetch(t);				
				} 
			}
			else{
				ungetch(c);			
			}
		}
		
		*w = c;
		w++;
		*w = '\0';
		return c;	
	}
	*w = '\0';
	return word[0];
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

void error(int c,char* s){
	printf("error: %s\n",s);
	while(c!=EOF && c!='\n')
		c = getch();
}

void skipblanks(void){
	int c;

	while((c = getch()) == ' ' || c == '\t'){
		;	
	}
	ungetch(c);
}

void getdef(void){
	int c,i;
	char def[MAXWORD],dir[MAXWORD], name[MAXWORD];

	skipblanks();
	
	if(!isalpha(getword(dir,MAXWORD)))
		error(dir[0],"expecting a directive after #");
	else if(strcmp(dir,"define") == 0){
		skipblanks();
		if(!isalpha(getword(name,MAXWORD))){
			error(name[0],"non-alpha name expected");
		}
		else{
			
			skipblanks();
			for(i = 0;i < MAXWORD-1;i++){
				if((def[i] = getch()) == EOF || def[i] == '\n') 
					break;	
			}
			def[i] = '\0';
			if(i <= 0){
				error('\n',"incomplete define");
			}
			else{
				install(name,def);
				printf("fetched from table %s for name (%s)\n",hashtab[hash(name)]->defn,name);		
			}	
		}
	}
	else if(strcmp(dir,"undef") == 0){
		skipblanks();
		if(!isalpha(getword(name,MAXWORD)))
			error(name[0],"non-alpha in undef");
		else{
			undef(name);
			printf("fetched from table address %u for name (%s) after undef",hashtab[hash(name)],name);
		}		
	}
	else{
		error(dir[0],"expecting a directive after #");
	}
}

void ungets(char s[]){
	int len = strlen(s);
	while(len--){
		ungetch(s[len]);
	}
}

int main(){
	char w[MAXWORD];

	struct nlist *p;
	
	while(getword(w,MAXWORD) != EOF){
		
		if(strcmp(w,"#") == 0){
			getdef();
		
		}
		else if(!isalpha(w[0])){
			printf("%s",w);		
		}else if((p = lookup(w)) == NULL){
			printf("%s",w);		
		}else
			ungets(p->defn);
	}
	return 0;
}

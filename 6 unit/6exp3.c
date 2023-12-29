#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100
#define YES 1
#define NO 0
#define SIZE 100000

int bufp = 0;
int buf[SIZE];

struct linklist{
	int lnum;
	struct linklist *ptr;
};

struct tnode {
	char* word;
	struct linklist *lines;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *talloc(void){
	return (struct tnode *) malloc(sizeof(struct tnode));
}


struct tnode *addtreex(struct tnode* p , char* w, int lines);
void treexprint(struct tnode *p);
int noiseword(char *);

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

	if(isalnum(c) || c == '_' || c == '#'){
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

struct linklist *lalloc(void){
	return (struct linklist *) malloc(sizeof(struct linklist));
}


void addln(struct tnode *p,int line){
	struct linklist *temp;
		
	temp  = p ->lines;
	while(temp->ptr != NULL && temp->lnum != line){
		temp = temp ->ptr;	
	}
	if(temp->lnum != line){
		temp->ptr = lalloc();
		temp->ptr->lnum = line;
		temp->ptr->ptr = NULL;	
	}
}




struct tnode *addtreex(struct tnode* p , char* w,int line){
	int cond;

	if( p == NULL){
		p = talloc();
		p->word = strdup(w);
		p->left = p->right = NULL;
		p->lines = lalloc();
		p->lines->lnum = line;
		p->lines->ptr = NULL;
	}
	else if((cond = strcmp(w,p->word)) < 0){
		p->left = addtreex(p->left,w,line);	
	}else if(cond > 0){
		p->right = addtreex(p->right,w,line);
	}else{
		addln(p,line);	
	}
	return p;
}

void treexprint(struct tnode *p){
	struct linklist *temp;
	if(p!=NULL){
		treexprint(p->left);
		printf("%10s: ",p->word);
		for(temp = p->lines;temp != NULL ;temp = temp->ptr){
			printf("%4d ",temp->lnum);		
		}
		printf("\n");
		treexprint(p->right);	
	}
}


int noiseword(char* w){
	static char *nw[] = {
		"a",
		"an",
		"and",
		"are",
		"in",
		"is",
		"of",
		"or",
		"that",
		"the",
		"this",
		"to"
	};

	int cond , mid;
	int low = 0;
	int high = sizeof(nw) / sizeof(char*) - 1;

	while(low <= high){
		mid = (low + high)/2;

		if((cond = strcmp(w,nw[mid])) < 0){
			high = mid -1;
		}
		else if(cond > 0){
			low = mid + 1;		
		}		
		else{
			return mid;
		}
	}	
	return -1;
}

int main(int argc,char* argv[]){
	struct tnode* root;
	int line = 1;
	char word[MAXWORD];
	root = NULL;

	while(getword(word,MAXWORD) != EOF){
		if(isalpha(word[0]) && noiseword(word) == -1){
			root = addtreex(root,word,line);
		}
		else if(word[0] == '\n'){
			line++;	
		}
	}

	treexprint(root);
	return 0;
}


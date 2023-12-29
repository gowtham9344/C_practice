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

struct tnode {
	char* word;
	int match;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *talloc(void){
	return (struct tnode *) malloc(sizeof(struct tnode));
}


struct tnode *addtreex(struct tnode* p , char* w, int num, int *found);
void treexprint(struct tnode *p);
int compare(char* s,struct tnode* p,int num, int *found);

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
	
	while(isspace(c = getch()))
		;

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
		*w = '\0';
		return c;	
	}
	
	
	*w = '\0';
	return word[0];
}


struct tnode *addtreex(struct tnode* p , char* w, int num, int *found){
	int cond;

	if( p == NULL){
		p = talloc();
		p->word = strdup(w);
		p->match = *found;
		p->left = p->right = NULL;
	}
	else if((cond = compare(w,p,num,found)) < 0){
		p->left = addtreex(p->left,w,num,found);	
	}else if(cond > 0){
		p->right = addtreex(p->right,w,num,found);
	}
	return p;
}

int compare(char* s,struct tnode* p,int num, int *found){
	int i;
	char *t = p->word;

	for (i = 0;*s == *t; i++,s++,t++)
		if(*s == '\0')
			return 0;
	if( i >= num){
		*found = YES;
		p->match = YES;	
	}
	return *s - *t;
}

void treexprint(struct tnode *p){
	if(p!=NULL){
		treexprint(p->left);
		if(p->match)
			printf("%s\n",p->word);
		treexprint(p->right);	
	}
}

int main(int argc,char* argv[]){
	struct tnode* root;
	char word[MAXWORD];
	int found = NO;

	int num = (--argc && (*++argv)[0] =='-') ? atoi(argv[0]+1):6;
	root = NULL;

	while(getword(word,MAXWORD) != EOF){
		if(isalpha(word[0] ) && strlen(word) >= num)
			root = addtreex(root,word,num,&found);
		found = NO;	
	}

	treexprint(root);
	return 0;
}


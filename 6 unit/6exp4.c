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
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *talloc(void){
	return (struct tnode *) malloc(sizeof(struct tnode));
}


struct tnode *addtreex(struct tnode* p , char* w);

struct tnode * list[1000];
int ntn = 0;

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




struct tnode *addtreex(struct tnode* p , char* w){
	int cond;

	if( p == NULL){
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if((cond = strcmp(w,p->word)) < 0){
		p->left = addtreex(p->left,w);	
	}else if(cond > 0){
		p->right = addtreex(p->right,w);
	}else{
		p->count++;	
	}
	return p;
}


void treestore(struct tnode* p){
	if( p!= NULL){
		treestore(p->left);	
		if(ntn < 1000)
			list[ntn++] = p;
		treestore(p->right);	
	}
}

void sortlist(){
	int gap,i,j;
	struct tnode* temp;
	
	for(gap = ntn/2;gap > 0;gap /=2){
		for(i = gap ; i < ntn ;i++){
			for(j = i -gap; j >=0 ;j-=gap){
				if((list[j]->count) >= (list[j+gap]->count))
					break;
				temp = list[j];
				list[j] = list[j+gap];
				list[j+gap] = temp;
			}		
		}
	}

}


int main(int argc,char* argv[]){
	struct tnode* root;
	int i;
	char word[MAXWORD];
	root = NULL;

	while(getword(word,MAXWORD) != EOF){
		if(isalpha(word[0])){
			root = addtreex(root,word);
		}
	}
	treestore(root);
	sortlist();
	
	for(i = 0;i< ntn;i++)
		printf("%2d : %20s \n",list[i]->count ,list[i]->word);
	return 0;
}


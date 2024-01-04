#include <unistd.h>
#include <stdio.h>

#define NALLOC 1024
#define MAXBYTES (unsigned)10240

typedef long Align;

union header {
    struct {
        union header *ptr; /* next block if on free list */
        unsigned size;     /* size of this block */
    } s;
};

typedef union header Header;

static unsigned maxalloc;
static Header base;
static Header *freep = NULL;


void free(void* ap){
	Header* bp,*p;
	bp = (Header*) ap - 1;
	if(bp->s.size > maxalloc){
		fprintf(stderr,"can't free %u units\n",bp->s.size);	
		return;	
	}

	for(p = freep;!(bp > p && bp < p->s.ptr); p = p->s.ptr){
		if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;	
	}

	if(bp + bp->s.size == p->s.ptr){
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;	
	}else{
		bp->s.ptr = p->s.ptr;
	}
	
	if(p + p->s.size == bp){
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;	
	}
	else{
		p->s.ptr = bp;	
	}
	
	freep = p;
}

unsigned bfree(char* p,unsigned n){
	Header* hp;
	
	if(n < sizeof(Header))
		return 0;
	hp = (Header*) p;
	hp->s.size = n / sizeof(Header);
	free((void*)(hp+1));
	return hp->s.size;
}

static Header *morecore(unsigned nu){
	char* cp;
	Header* up;
	
	if(nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if( cp == (char*) -1){
		return NULL;	
	}
	up = (Header*) cp;
	up->s.size = nu;
	maxalloc = (up->s.size > maxalloc) ? up->s.size : maxalloc;
	free((void*)(up+1));
	return freep;
}

void* malloc1(unsigned nbytes){
	Header *p,*prevp;
	unsigned nunits;

	if(nbytes > MAXBYTES){
		fprintf(stderr,"can't allocate more than %u bytes\n",MAXBYTES);
		return NULL;	
	}
	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	
	if((prevp = freep) == NULL){
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;	
	}

	for(p = prevp->s.ptr; ;prevp = p, p = p->s.ptr){
		if(p->s.size >= nunits){		
			if(p->s.size == nunits){
				prevp->s.ptr = p->s.ptr;		
			}
			else{
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;		
			}
			freep = prevp;
			return (void *) (p+1);	
		}
		if(p == freep)
			if((p = morecore(nunits)) == NULL)
				return NULL;
	}
}


int main(){
	char* p = NULL;
	char i =0;
	int n = 1000;
	
	p = malloc1(n*sizeof(*p));
		
	if(p == NULL){
		printf("malloc can't able to allocate memory\n");	
	}
	else{
		for(i = 0; i<10;i++){
			printf("%d\n",p[i]);					
		}	
		printf("\n");
		printf("Size of freed block in header sized units is  %u\n",bfree(p,n*sizeof(*p)));
	}
	return 0;
}




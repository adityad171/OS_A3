#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

typedef struct node{
    char str[100];
    int IND;
}Node;

#define SHM_SIZE 7 * sizeof(Node)

char strings[50][11];
void WORD_GEN(int len){
    for(int i=0; i<50; i++){
        strings[i];
        char string[len+1];

        for(int i=0; i<len;i++){
        
            int asciino;
            asciino = (rand()%26)+65;
            string[i] = (char)asciino;
        }
        string[len]='\0';
        strcpy(strings[i],string);
    }
}



int FLAG1=0;


int main()
{
    static int ind=0;
    WORD_GEN(10);
    int fd = shm_open("/abhishek", O_CREAT | O_RDWR, 0600);
    if (fd < 0) {
        printf("Error creating shm object\n");
        return EXIT_FAILURE;
    }

    ftruncate(fd, SHM_SIZE);
    Node* data = (Node*) mmap(0, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    data[6].IND=0;

    while(FLAG1==0){
        while(data[6].IND!=0);
        for(int itr=0; itr<5; itr++){
            //char buff[100];
            //strcpy(buff,strings[ind]);
            strcpy(data[itr].str,strings[ind]);
            data[itr].IND=ind;
            //printf("%s %d\n",data[itr].str,data[itr].idx );
            if(ind==49){
                FLAG1=1;
                break;
            }
            ind++;
            //printf("%d\n", ind);
            
        }

        data[6].IND=1;
        //printf("%d\n",data[6].idx);
        

        while(data[6].IND!=2);
        printf("From Sender: %s %d\n",data[5].str,data[4].IND);

        ind = data[5].IND;

        printf("%d\n", ind);

        data[6].IND=0;

    }


    
    munmap(data,SHM_SIZE);
    close(fd);
    return EXIT_SUCCESS;
}
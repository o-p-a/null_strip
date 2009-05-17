/*
    strip null starting
*/

#include <stdio.h>

void strip_null_starting(char *filename)
{
    FILE *ifp;
    FILE *ofp;
    int c;

    ifp=fopen(filename,"rb");
    ofp=fopen("$$$null_strip_temp$$$","wb");

    if(ifp==NULL || ofp==NULL){
        fprintf(stderr,"null_strip: fopen failed\n");
        fclose(ofp);
        fclose(ifp);
        return;
    }

    while(1){
        c=fgetc(ifp);
        if(c==EOF)
            break;
        if(c!='\0'){
            ungetc(c,ifp);
            break;
        }
    }

    while(1){
        c=fgetc(ifp);
        if(c==EOF)
            break;
        fputc(c,ofp);
    }

    fclose(ofp);
    fclose(ifp);
}

int main(int ac,char *av[])
{
    int i;

    if(ac<=1){
        printf("usage: null_strip <filenames>\n");
        return 1;
    }else{
        for(i=1;i<ac;i++)
            strip_null_starting(av[i]);
        return 0;
    }
}


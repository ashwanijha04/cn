#include<stdio.h>
#include<string.h>
#define N strlen(divisor)

// t : data
// cs : CheckSum 
// a = length of databits
// g : divisor
// N : Divisor Length


char data[28],checksum[28],divisor[16];
int datalength,error;
int i;

void xor(){
    for(i = 1; i< N; i++)
    checksum[i] = (( checksum[i] == divisor[i])?'0':'1');
}

void crc(){
    for(error=0; error<N; error++)
        checksum[error]=data[error];
    
    do{
        if(checksum[0]=='1')
            xor();
        for(i=0; i<N-1; i++)
            checksum[i]=checksum[i+1];
        checksum[i]=data[error++];
    }while(error<=datalength+N-1);
}

int main()
{
    printf("\nEnter data : ");
    scanf("%s",data);
    printf("\n----------------------------------------");

    printf("\nEnter divisor: ");
    scanf("%s", divisor);

    datalength = strlen(data);

    for(error=datalength;error<datalength+N-1;error++)
        data[error]='0';

    printf("\n----------------------------------------");
    printf("\nModified data is : %s",data);
    printf("\n----------------------------------------");


    crc();


    printf("\nChecksum is : %s",checksum);

    for(error=datalength;error<datalength+N-1;error++)
        data[error]=checksum[error-datalength];

    printf("\n----------------------------------------");
    printf("\nFinal codeword is : %s",data);
    printf("\n----------------------------------------");
    printf("\nTest error detection 0(yes) 1(no)? : ");
    scanf("%d",&error);

    if(error==0)
    {
        do{
            printf("\nEnter the position where error is to be inserted : ");
            scanf("%d",&error);
        }while(error==0 || error>datalength+N-1);

        data[error-1]=(data[error-1]=='0')?'1':'0';
        printf("\n----------------------------------------");
        printf("\nErroneous data : %s\n",data);
    }

    crc();
    for(error=0;(error<N-1) && (checksum[error]!='1');error++)
     ;
        if(error<N-1)
            printf("\nError detected, syndrome bits are: %s\n\n", checksum);
        else
            printf("\nNo error detected, syndrome bits are: %s\n\n", checksum);
            printf("\n----------------------------------------\n");
        return 0;
}

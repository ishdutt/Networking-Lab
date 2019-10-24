#include<stdio.h>
 
int main()
{
    int w,j,i,f,frames[50];
 
    printf("Enter window size: ");
    scanf("%d",&w);
 
    printf("\nEnter number of frames to transmit: ");
    scanf("%d",&f);
 
    printf("\nEnter %d frames: ",f);
 
    for(i=1;i<=f;i++)
        scanf("%d",&frames[i]);
    
    //Enter the lost frame index
    int lost=0;
    int flag=0;
    printf("Enter the frame to be lost ");
    scanf("%d",&lost);
    
    printf("\nWith sliding window protocol the frames will be sent in the following manner (assuming no corruption of frames)\n\n");
    printf("After sending %d frames at each stage sender waits for acknowledgement sent by the receiver\n\n",w);
 
    for(i=1;i<=f;i+=w)
    {
	for(j=i;j<i+w&&j<=f;j++)
	{
		printf("%d ",j);
	}
	if(j>lost && flag==0)
	{
		flag=1;
		i=i-w;
		printf("Corrupted data encountered ...the frame will be resent\n");	
	}
	printf("\nThe ack is sent\n");
    }
 
    if(f%w!=0)
        printf("\nAcknowledgement of above frames sent is received by sender\n");
 
    return 0;
}

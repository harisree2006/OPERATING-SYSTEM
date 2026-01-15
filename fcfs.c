#include<stdio.h>

int main(){
	int n,at[4],bt[4],ct[4],wt[4],tat[4];
	int time = 0;
	float avg_wt = 0,avg_tat=0;
	
	printf("Enter number of processor : ");
	scanf("%d",&n);	
	
	for(int i=0;i<n;i++){
		printf("Process %d arrival time: ",i+1);
		scanf("%d",&at[i]);
		printf("Process %d brust time: ",i+1);
		scanf("%d",&bt[i]);
	}
	
	ct[0] = at[0]+bt[0];
	for(int i=1;i<n;i++){
		if(ct[i-1]<at[i])
			ct[i] = at[i]+bt[i];
		else
			ct[i]=ct[i-1]+bt[i];
	}
	
	for(int i=1;i<n;i++){
		tat[i]=ct[i]-at[i];
		wt[i]=tat[i]-bt[i];
		avg_wt += wt[i];
		avg_tat += tat[i];
	}
		
	printf("\nFCFS Sheduling\n");
	printf("Process\tAT\tBT\tWT\tTAT\n");
	
	for(int i=0;i<n;i++){
		printf("P%d\t%d\t%d\t%d\t%d\n", i+1,at[i],bt[i],wt[i],tat[i]);
	}
	
	printf("Average Waiting TIme = %2f\n",avg_wt/n);
	printf("Average Turn Around TIme = %2f\n",avg_tat/n);
	return 0;
	
}


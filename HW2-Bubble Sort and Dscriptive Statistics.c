#include <stdio.h>
#include <stdlib.h>

int main(void)
{
       
FILE *out, *in;

int num;//�ŧi�}�C���Ӽ� 
int s[100];//�}�C��100�ӼƦr 
int i;
void BubbleSort(int[], int);//�ŧi�w�j�ƧǨ�� 
float average(int[],int);//�ŧi�����ƨ�� 
float variance(int [],int,float);//�ŧi�ܲ��ƨ�� 
float average_result,variance_result;//�ŧi������,�ܲ��� 

out = fopen("output.dat", "w");//�N���G�g�Joutput�� 
in = fopen("input.dat", "r");//Ū��input�� 
fscanf(in, "%d\n", &num);//Ū���}�C���Ӽ� 

for (i =0; i <num; i++) // Ū��input.dat�ĤG�檺�Ʀr
{				
    fscanf(in,"%d",&s[i]);				 				
}




BubbleSort(s, num); //����w�j�ƧǨ��
fprintf(out,"�Ʀr�Ѥp��j�O " );
for(i=1; i<=num;i++){                                     //�g�Joutput�� 
             fprintf(out,"%d ",s[i-1] );
			
    }

average_result=average(s,num);//�⥭����

variance_result=variance(s,num,average_result);//���ܲ��� 


fprintf(out,"\n average=%.2f\n ",average_result);//�L�ܲ��ƤΥ����� 
fprintf(out,"variance=%.2f \n",variance_result);


fclose(in);
fclose(out);
 
  
  system("PAUSE");	
  return 0;
}

//Bubblesort�ƧǪk �N�Ʀr�Ѥp��j�ƦC 
void BubbleSort(int data[], int num){
    int i, j, temp;
    for (i = num; i > 1; i--){
       for (j = 1; j < i; j++){
          if (data[j-1] >data[j]){
             temp = data[j-1];
             data[j-1] = data[j];
             data[j] = temp;
          }
       }
    }
}

//�����ƨ�� 
float average  (int s[ ],int num){                      
      float   answer=0;
      float   sum=0;
      int i;
      for(i=1;i<=num;i++){
               sum +=  s[i-1];
      }
      
      answer = (float)sum/num;
      return answer;
}

 
//�ܲ��ƨ�� 
float variance(int s[ ],int num,float average){       
      
      float  answer=0;
      float  sum=0;
      int i;
      for(i=1; i<=num;i++){
               sum +=  (s[i-1]-average)*(s[i-1]-average);
      }
      
      
      
      answer = (float)sum / (float)num;
      return answer;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
 float temperature;
 float R_CtoF,R_FtoC;//temperature�@�}�l��J���ū�, 
 float F_CtoF(float );//�ഫ���ؤ󪺨��
 float F_FtoC(float); //�ഫ����󪺨�� 
 printf("please input the temperature\n");
 scanf("%f",&temperature);
 	
 
 if(temperature>=20&&temperature<=45)// �Y�OŪ�����ƭȤ���20�]�t�^��45�]�t�^�����A�N�O���A�n�N���ন�ؤ�� �A��round�|�ˤ��J���� 
 {
     printf("the temperature you input is in degree Celsius.\n");
     R_CtoF= F_CtoF(temperature); 
     printf("%f ���׵��� %f �ؤ�� .\n",temperature,round(R_CtoF));                             
 }
 else if(temperature>=68&&temperature<=113)//�Y�O�Y�OŪ�����ƭȤ���68�]�t�^��113�]�t�^�����A�N�O�ؤ�A�n�N���ন���סA��round�|�ˤ��J����  
 {
      printf("the temperature you input is in degree Fahrenheit.\n");
     R_FtoC= F_FtoC(temperature);
     printf("%f �ؤ�׵��� %f ���� .\n",temperature,round(R_FtoC));    
}
//��J���ū׭Y���b20��45�����A�]���b68��113�����A�h�O���X�z����J��l�h�����X�z��J 
 else{
      printf("illegal input\n");    
}
 

 system("pause");
 return 0;
}

float F_CtoF(float temperature )//�ഫ���ؤ󪺨�� 
{
      float R_CtoF;
      R_CtoF= temperature*9/5+32;
      return R_CtoF;   
} 

float F_FtoC(float temperature)//�ഫ����󪺨�� 
{
      float R_FtoC;
      R_FtoC=(temperature-32)*5/9;
      return R_FtoC;
}









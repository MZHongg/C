#include <stdio.h>
#include <math.h>

#define FALSE 0
#define TRUE 1
#define ARRIVAL 2
#define DEPT 3
#define LIMITS 100.0


//�ŧi��Ƶ��c�A����Ƶ��c�]�t�ɶ��Ψƥ�����(��F�ΎͬO���}) 
typedef struct _Entity {
    int type;
    float time;
} Entity;


Entity event[100]; //���}�C��100���ܼ� 
Entity queue[100]; //���}�C��100���ܼ� 
int seed = 23456789;//�ؤl�����l�ȬO23456789 


int main(void){
    int num_events = 0, num_queue = 0; //�ŧi�ƥ�Ƥαƶ��H�ơA�ó]�w���l�Ȭ�0 
    float next_time;                   //�٭n�L�h�[�U���U�Ȥ~�|��   
    float time = 0.0;                  //�ثe���ɶ� 
    int Server_Is_Idle = TRUE;          
    float arrival_rate;                //��F�v(�����@�p�ɩ�F�h�֤H) 
    float service_rate;                //�A�Ȳv(�����@�p�ɥi�H�A�Ȧh�֤H) 
    int type;                          //�ƥ����� 
//�p��t�Τ������H�ơC
//�p��t�Τ��������ԡ]�ƶ��^�H�ơC
    
    printf(" please input arrival rate per hour:  \n"); //'���ϥΎͿ�J��F�v 
    scanf("%f",&arrival_rate);
    printf(" please input service rate per hour: \n");  //���ϥΎͿ�J�A�Ȳv 
    scanf("%f",&service_rate);

    
    
    void GenerateFirstEvent(float, float, int *);  //�ŧi���ͲĤ@�Өƥ󪺨�� 
    float GenerateTime(float);                     //�ŧi���ͮɶ������ 
    void InsertEvent(float, int *, float, int);    //�ŧi���J�ƥ󪺨��  
    void PutInQueue(int *, float);                 //�ŧi�ƶ������ 
    void GetFromQueue(float, int *, int *, float); //�ŧi���H�q�ƶ������}�����  
    void DeleteFirstEvent(int *);                  //�R���Ĥ@�Өƥ��� 
    void PrintEvent(int), PrintQueue(int);         // �L�X�ƥ��ƶ��ƥ� 
    
    int Nt=0,Qt=0;                                  //�t�Τ����`�H��,�ƶ����`�H��
    float Avg_Nt=0,Avg_Qt=0;                          //�����t�ΤH��,�����ƶ��H��
    float total_Nt = 0.0,total_Qt=0;                //�ɶ��[�v�t�Τ����`�H��,�ɶ��[�v�ƶ����`�H��
    
    
    
    
    GenerateFirstEvent(time, arrival_rate, &num_events);//���ͲĤ@�Өƥ�A�ƥ�Ʒ|����
    printf("cehck GenerateFirstEvent\n");
    PrintEvent(num_events);                            //���L�X���ˬd�{�����L���� 
    PrintQueue(num_queue);                             //���L�X���ˬd�{�����L����
   // printf("cehck GenerateFirstEvent over\n");
    
    
   
  while(time <= LIMITS){
        total_Nt = total_Nt+(event[0].time - time)*Nt;//�ɶ��[�v�t�Τ����`�H��
		total_Qt = total_Qt+(event[0].time - time)*Qt;//�ɶ��[�v�ƶ����`�H��       
        time = event[0].time; // ���X�Ĥ@�Өƥ�G�ثe���ɶ�����Ĥ@�Өƥ󪺮ɶ� 
        type = event[0].type; // ���X�Ĥ@�Өƥ�G���ƥ����� 
        DeleteFirstEvent(&num_events);//�]�����X�ӤF�Ĥ@�Өƥ�A�n�R�� 
        PrintEvent(num_events); //�ݬݥثe�ƥ�ƬO�_�O0(�]���R���F) 
        
        
        if(type == ARRIVAL){
            Nt++;                                    //���H�i�Өt�ΤF,�t�ΤH��+1  
            next_time = GenerateTime(arrival_rate);  //�Ĥ@�Өƥ��F�ɪ��ɶ� 
            InsertEvent(time, &num_events, next_time, ARRIVAL);  //���J�ƥ� 
            PrintEvent(num_events);
            
            //�p�G�A�ȤH���{�b���� 
            if(Server_Is_Idle == TRUE){
                next_time = GenerateTime(service_rate);
                InsertEvent(time,&num_events, next_time, DEPT);
                Server_Is_Idle = FALSE;//�]���A�ȭ����b�A�ȫȤH�A�S�� 
                PrintEvent(num_events);
            }
            //�p�G�A�ȤH���{�b�u�S�v����  
            else{
                 Qt++;                             //�p�G�t�Υ��b���L,�ƶ��H��+1 
                
                PrintQueue(num_queue);
                PutInQueue(&num_queue, time);//�p�G�A�ȭ��S�šA�N�h�ƶ��A&num_queue�����ܱƶ��H�� 
                PrintQueue(num_queue);
            }
        }
        //�p�G�O���}�ƥ� 
        else if(type ==DEPT){
             Nt--;                         //�t�ΤH��-1                                    
            //�p�G�ƶ��H�Ƥ�����0�A�����H�N�n�q�ƶ������}�A�h���A�ȭ��A��(�]�����H�Q�A�ȭ��A�ȧ�����A���}) 
            if(num_queue != 0){ 
                Qt--;
                PrintEvent(num_events);
                PrintQueue(num_queue);
                GetFromQueue(time, &num_events, &num_queue, service_rate);//���H�n�q�ƶ������}�A�h���A�ȭ��A��(�]�����H�Q�A�ȭ��A�ȧ�����A���})
                PrintEvent(num_events);  
                PrintQueue(num_queue); 
            }else
              //�p�G�S���H�b�ƶ��A����{�b�A�ȭ��N�O�Ŷ���  
              {
                Server_Is_Idle = TRUE;
              }
        }
    }   
    
  
    Avg_Nt=(total_Nt/event[0].time);
    Avg_Qt=(total_Qt/event[0].time);
    printf("The average number of customer in system is: %f\n",Avg_Nt);
    printf("The average queneing number of customer in system is: %f\n",Avg_Qt);
    system("pause");
}
 

//���ͲĤ@�Өƥ� GenerateFirstEvent(time, arrival_rate, &num_events)
void GenerateFirstEvent(float time, float rate, int *num){
    float GenerateTime(float);
    void PrintEvent(int);
    
    event[0].time = time + GenerateTime(rate); // �Ĥ@�Өƥ󪺩�F�ɶ��|����ثe�ɶ��[�W�g�L�h�[��|��F���ɶ�(�Ω�F�v��) 
    event[0].type = ARRIVAL;                   //�Ĥ@�Өƥ������O��F�ƥ�  
    
    (*num)++; //�쥻�ƥ�ƬO0�A�A���ͤ@�ӷs�ƥ��A�ثe�ƥ�Ƭ�1 
}


void PrintEvent(int num){
    int i;
    
    printf("*** total event number is %d ***\n",num);
    
    for(i = 0; i < num; i++){
        printf("type is %d, time is %f\n", event[i].type, event[i].time);
    }
}



void PrintQueue(int num){
    int i;
    
    printf("*** total queue number is %d ***\n", num);
    
    for(i = 0; i < num; i++){
        printf("type is %d, time is %f\n", queue[i].type, queue[i].time);
    }
}





//�R���Ĥ@�Өƥ� 
void DeleteFirstEvent(int *num){
    int i;
    
    for(i = 0; i < *num; i++){
        event[i].type = event[i+1].type;
        event[i].time = event[i+1].time;
    }
    (*num)--;//�]���R���ƥ�A�ҥH�ƥ�ƴ�1 
}





float GenerateTime(float rate){
    float rn, time;
    float GetRandomNumber(void);
    float GetExponential(float, float);
    
    rn = GetRandomNumber();
    time = GetExponential(rn, rate);
    return(time);
}





// InsertEvent(time, &num_events, next_time, ARRIVAL) 
void InsertEvent(float time, int *num, float next_time, int type){
    int target;
    float value = time + next_time;//�ĤG�Өƥ��F�ɪ��ɶ� 
                
    if(*num == 0){
        event[0].time = value;
        event[0].type = type;
        *num = 1;
        return;
    }
    
   // PrintEvent(*num);
    
    target = *num - 1;
    
    //�@������target�p��0�A�]�N�O�ƥ�Ƥp��1�A 
    while(target >= 0 && event[target].time > value){
        event[target+1].time = event[target].time;
        event[target+1].type = event[target].type;
        target--;
    }
    event[target+1].time = value;
    event[target+1].type = type;
    
    (*num)++;                //���J�@�Өƥ��A�ثe���ƥ�ƭn�[�@ 
}


//�ƶ� PutInQueue(&num_queue, time)
void PutInQueue(int *num_queue, float time){
    queue[*num_queue].type = ARRIVAL;
    queue[*num_queue].time = time;
    (*num_queue)++;          //�ƶ��H�ƼW�[�@�H 
}


// GetFromQueue(time, &num_events, &num_queue, service_rate) 
void GetFromQueue(float time, int *num_events, int *num_queue, float service_rate){
    float next;
    float GenerateTime(float);
    void InsertEvent(float, int *, float, int);
    int i;
    
    next = GenerateTime(service_rate); // 
    InsertEvent(time, num_events, next, DEPT); //(float time, int *num, float next_time, int type) 
    
    for(i = 0; i < *num_queue-1; i++){
        queue[i].type = queue[i+1].type; //��᭱������e�� 
        queue[i].time = queue[i+1].time;
    }
    (*num_queue)--; //�ƶ��H�Ƥֱ��@�ӤH 
}


float GetRandomNumber(void){
    float random;
    
    seed = fmod((double)16807*seed, (double)2147483647);
    random = (float)seed/2147483647;
    return(random);
}


float GetExponential(float rn, float rate){    
    return(log((1.0 - rn))/(-1.0 * rate));
}

#include<iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <string.h>
#include<math.h>
#include<vector>
#include <cstdlib> 
using namespace std;



string read_instructions(string instruction [],string rd[],string rs[],string rt[],string sa[],string offset[],string imm[],int a[],int b[],int pc){
    vector<string> v;
    stringstream check(instruction[pc]);
        string inter;
        while(getline(check,inter,' ')){
           v.push_back(inter);
        }
   // cout<<v[0]<<endl;
if(v[0].compare("add")==0){//add

                  
                     rd[pc]=v[1].substr(1,v[1].length()-1);
                     rs[pc]=v[2].substr(1,v[2].length()-1);
                     rt[pc]=v[3].substr(1,v[3].length()-1);
                       // sa="0";
                     a[pc]=0;
                     b[pc]=0;
        
        }else if(v[0].compare("sub")==0){//sub
                    
                     rd[pc]=v[1].substr(1,v[1].length()-1);
                     rs[pc]=v[2].substr(1,v[2].length()-1);
                     rt[pc]=v[3].substr(1,v[3].length()-1);
                    // sa="0";
                    a[pc]=0;
                    b[pc]=0;
                
        }
        else if(v[0].compare("sll")==0){
                    
                    rs[pc]="0";
                     rd[pc]=v[1].substr(1,v[1].length()-1);
                     rt[pc]=v[2].substr(1,v[2].length()-1);
                     sa[pc]=v[3];
                     a[pc]=0;
                     b[pc]=0;
        }else if(v[0].compare("srl")==0){
                    
                    rs[pc]="0";
                     rd[pc]=v[1].substr(1,v[1].length()-1);
                     rt[pc]=v[2].substr(1,v[2].length()-1);
                     sa[pc]=v[3];
                     a[pc]=0;
                     b[pc]=0;
            

        }else if(v[0].compare("lw")==0){
            rs[pc]=v[1].substr(1,v[1].length()-1);
            rt[pc]=v[2].substr(1,v[2].length()-1);
            rd[pc]="0";
            offset[pc] = v[3];
            
             a[pc]=1;
             b[pc]=1;
           

        }else if(v[0].compare("sw")==0){

            rs[pc]=v[1].substr(1,v[1].length()-1);
            rt[pc]=v[2].substr(1,v[2].length()-1);
            //rt3=rt;
            rd[pc]="0";
            //sa="0";
            offset[pc] = v[3];
           a[pc]=1;
           b[pc]=1;
        }else if(v[0].compare("beq")==0){//beq
                
                     rs[pc]=v[1].substr(1,v[1].length()-1);
                     rt[pc]=v[2].substr(1,v[2].length()-1);
                     rd[pc]="0";
                     imm[pc]=v[3];
                     //sa="0";
                     a[pc]=0;
                     b[pc]=0;
                     

            
        }else if(v[0].compare("bne")==0){//bne
                
                     rs[pc]=v[1].substr(1,v[1].length()-1);
                     rt[pc]=v[2].substr(1,v[2].length()-1);
                     rd[pc]="0";
                     imm[pc]=v[3];
                     //sa="0";
                     a[pc]=0;
                     b[pc]=0;
                     

                   
        }
        else if(v[0].compare("bgtz")==0){//bgtz
                
                     rs[pc]=v[1].substr(1,v[1].length()-1);
                     rd[pc]="0";
                     rt[pc]="0";
                     imm[pc]=v[2];
                     //sa="0";
                     a[pc]=0;
                     b[pc]=0;
                    
                     
        }else if(v[0].compare("bltz")==0){//bltz
                
                     rs[pc]=v[1].substr(1,v[1].length()-1);
                     rd[pc]="0";
                     rt[pc]="0";
                     imm[pc]=v[2];
                    // sa="0";
                     a[pc]=0;
                     b[pc]=0;
                                 
        }else if(v[0].compare("j")==0){//jump
                    rs[pc]="0";
                     rd[pc]="0";
                     rt[pc]="0";
                     imm[pc]=v[1];
                    // sa="0";
                     a[pc]=0;
                     b[pc]=0;
        }
        return v[0];
}        


int alu(string opcode[],int op1,int op2,string sa[],int a[],int b[],int pc){
  int value=0;  
 
 if(opcode[pc].compare("add")==0){value= op1+op2;a[pc]=0;b[pc]=0;}
 else if(opcode[pc].compare("sub")==0){value= op1-op2;a[pc]=0;b[pc]=0;}
 else if(opcode[pc].compare("sll")==0){value=op2*pow(2,stoi(sa[pc]));a[pc]=0;b[pc]=0;}
 else if(opcode[pc].compare("srl")==0){value=op2/pow(2,stoi(sa[pc]));a[pc]=0;b[pc]=0;}
 else if(opcode[pc].compare("lw")==0){value=op1+op2;a[pc]=1;b[pc]=0;}
 else if(opcode[pc].compare("sw")==0){value=op1+op2;a[pc]=0;b[pc]=1;}

 return value; 
}








int main(){
	ifstream file("input_9.txt"); 
    string word, t, q, filename; 
    string ins[128];
    int k=0;
    string line;
     while (getline(file,line))
    { 
            
            ins[k]=line;
            k++;
        

    } 
    string opcode[1000]={" "};
    string rs[1000]={" "};
    string rt[1000]={" "};
    string rd[1000]={" "};
    string instruction[10000]={" "};
    string sa[1000]={" "};
    string offset[1000]={" "};
    string imm[1000]={" "};
    //string opcode[k]={" "};
    int mux_RegDst[1000]={0};
    int mux_AluSrc[1000]={0};
    int mux_MemRead[1000]={0};
    int mux_MemWrite[1000]={0};
    int mux_RegWrite[1000]={0};
    int mux_MemtoReg[1000]={0};
    int branch[1000]={0};
    int value[1000]={0};
    int read_data1=0;
    int read_data2=0;
    int write_data[1000]={0};
    int pc[1000]={0};
    int bubble[1000]={0};
    int ins_number[1000]={0};
    int stall[1000]={0};
    int forwarding_rs[1000]={0};
    int forwarding_rt[1000]={0};
    //int write_data2=0;
    int dest[1000]={0};
    long long int reg[32]={0};
    int cycle=0;
    int num=0;
    float avg=0;
    reg[8]=8;
    reg[9]=9;
    reg[10]=10;
    ins[8]="13";
    ins[9]="14";
    ins[14]="15";
    ins[10]="10";
   // ins[8]="13";
   // ins[9]="14";
    
    int j=0;
    int p=0;
    while(j<k+4){
        if(j<k)
        {
           instruction[p] = ins[j];
           ins_number[p]=j;
            cout<<instruction[p]<<endl;
            cout<<"ins "<< j<<" stage0"<<endl;
            
       
       }
       //cout<<branch[p-1]<<endl;

       if(cycle>=4 &&  j<k+4){
             
             if(bubble[p-4]==1){
                cout<<"bubble stage4"<<endl;
            }
            else{
                if(mux_RegWrite[p-4]==1){
                //cout<<dest[j-4]<<endl;
                    reg[dest[p-4]]=write_data[p-4];
                }
            
                  cout<<"ins "<< ins_number[p-4]<<" stage4"<<endl;
            }
       }
       // cout<<branch[p-1]<<endl;
       if(cycle>=1 && j<k+1){
            //cout<<opcode[j-1]<<endl;
            //cout<<bubble[j-1]<<endl;
            if(bubble[p-1]==1){
                cout<<"bubble stage1"<<endl;
            }
            else{

                opcode[p-1]=read_instructions(instruction,rd,rs,rt,sa,offset,imm,mux_RegDst,mux_AluSrc,p-1);
               // cout<<opcode[j-1]<<endl;
               // cout<<opcode[p-1]<<endl;
                 if(opcode[p-1].compare("beq")==0){
                        if(reg[stoi(rs[p-1])]==reg[stoi(rt[p-1])]) {pc[p-1]=stoi(imm[p-1]);branch[p-1]=1;}
                  }
                 else if(opcode[p-1].compare("bne")==0){
                        if(reg[stoi(rs[p-1])]!=reg[stoi(rt[p-1])]) {pc[p-1]=stoi(imm[p-1]);branch[p-1]=1;}
                  }
                 else if(opcode[p-1].compare("bgtz")==0){
                        if(reg[stoi(rs[p-1])]>0) {pc[p-1]=stoi(imm[p-1]);branch[p-1]=1;}
                  }
                 else if(opcode[p-1].compare("bltz")==0){
                        if(reg[stoi(rs[p-1])]<0) {pc[p-1]=stoi(imm[p-1]);branch[p-1]=1;}
                  }
                   else if(opcode[p-1].compare("j")==0){
                        pc[p-1]=stoi(imm[p-1]); branch[p-1]=1;
                  }
                 
                  if(p>=2){
                        //cout<<ins_number[p-2]<<" "<<ins_number[p-1]<<endl;
                    if(mux_RegDst[p-2]==0){
                       if(rs[p-1].compare(rd[p-2])==0 || rt[p-1].compare(rd[p-2])==0){
                            if(rs[p-1].compare(rd[p-2])==0) forwarding_rs[p-1]=1;
                            if(rt[p-1].compare(rd[p-2])==0) forwarding_rt[p-1]=1;
                       }
                    }
                    else{
                        if(opcode[p-2].compare("lw")==0){
                        if(rs[p-1].compare(rt[p-2])==0 || rt[p-1].compare(rt[p-2])==0){
                            if(rs[p-1].compare(rt[p-2])==0) forwarding_rs[p-1]=1;
                            if(rt[p-1].compare(rt[p-2])==0) forwarding_rt[p-1]=1;
                            }
                        }
                    }
                        
                }

                if(p>=3){
                    if(mux_RegDst[p-3]==0){
                    
                       if(rs[p-1].compare(rd[p-3])==0 || rt[p-1].compare(rd[p-3])==0){
                            if(rs[p-1].compare(rd[p-3])==0) forwarding_rs[p-1]=2;
                            if(rt[p-1].compare(rd[p-3])==0) forwarding_rt[p-1]=2; 
                        }
                    }

                    else{
                      if(opcode[p-2].compare("lw")==0){  
                       if(rs[p-1].compare(rt[p-3])==0 || rt[p-1].compare(rt[p-3])==0){
                            if(rs[p-1].compare(rt[p-3])==0) forwarding_rs[p-1]=2;
                            if(rt[p-1].compare(rt[p-3])==0) forwarding_rt[p-1]=2;
                            }     
                        }
                    }    

                }

                cout<<"ins "<< ins_number[p-1]<<" stage1"<<endl;
                    }
            }
               
       if(cycle>=2 && j<k+2){

            if(bubble[p-2]==1){
                cout<<"bubble stage2"<<endl;
            }

            else{
                if(forwarding_rs[p-2]==0) read_data1=reg[stoi(rs[p-2])];
                else {
                    if(forwarding_rs[p-2]==1) 
                        {
                            if(mux_RegDst[p-3]==0){read_data1=value[p-3];}
                            else{if(opcode[p-3].compare("lw")==0) read_data1=stoi(ins[value[p-3]]);}
                        }

                     else{
                            if(mux_RegDst[p-4]==0){read_data1=value[p-4];}
                            else{if(opcode[p-4].compare("lw")==0) read_data1=stoi(ins[value[p-4]]);}
                     }   
                     
                }

                
                if(mux_AluSrc[p-2]==0){
                  
                   if(forwarding_rt[p-2]==0)read_data2=reg[stoi(rt[p-2])];
                   else{

                       if(forwarding_rt[p-2]==1) 
                        {
                            if(mux_RegDst[p-3]==0){read_data2=value[p-3];}
                            else{if(opcode[p-3].compare("lw")==0) read_data2=stoi(ins[value[p-3]]);}
                        }

                     else{
                            if(mux_RegDst[p-4]==0){read_data2=value[p-4];}
                            else{if(opcode[p-4].compare("lw")==0) read_data2=stoi(ins[value[p-4]]);}

                        } 
                   } 


                 }
                else{read_data2=stoi(offset[p-2]);}
            
                if(mux_RegDst[p-2]==0){dest[p-2]=stoi(rd[p-2]);}
                else{dest[p-2]=stoi(rt[p-2]);}
                //cout<<stoi(sa[j-2])<<endl;

                value[p-2]=alu(opcode,read_data1,read_data2,sa,mux_MemRead,mux_MemWrite,p-2);
                //cout<<value[p-2]<<endl;
                 cout<<"ins "<< ins_number[p-2]<<" stage2"<<endl;
            }    
       }
        //cout<<branch[p-1]<<endl;
       if(cycle>=3 && j<k+3){
           //  mux_RegWrite=0;
            if(bubble[p-3]==1){
                cout<<"bubble stage3"<<endl;
            }

            else{
                if(mux_MemRead[p-3]==0){write_data[p-3]=value[p-3];mux_MemtoReg[p-3]=0;mux_RegWrite[p-3]=1;}

                else{ write_data[p-3]=stoi(ins[value[p-3]]);mux_MemtoReg[p-3]=1;mux_RegWrite[p-3]=1;}

                if(mux_MemWrite[p-3]==1){ins[value[p-3]]=to_string(reg[stoi(rt[p-3])]);mux_RegWrite[p-3]=0;}
                cout<<"ins "<< ins_number[p-3] <<" stage3"<<endl;
            }
       }
       //cout<<branch[p-1]<<endl;
       

       
       
      if(cycle>=1) {
        if(branch[p-1]==1) {bubble[p]=1;j=j+pc[p-1]-1;}
        else j= j+1+pc[p-1];
    }  
      else j++; 
      // cout<<p<<" "<<bubble[p]<<endl;
       p++;
       cycle++;
     
       //cout<<"j= "<<j<<endl;
       //cout<<reg[11]<<endl;
       cout<<"CYCLE "<<cycle<<endl;

    }
    for(int i=0;i<32;i++){
            cout<<"reg"<<i<<" = "<<reg[i]<<endl;
        }
    cout<<ins[9]<<endl;    
    cout<<ins[10]<<endl;
    avg=(float)k/cycle;
    cout<<"IPC = "<<avg<<endl; 

}
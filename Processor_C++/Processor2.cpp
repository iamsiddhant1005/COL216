
#include<iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <string.h>
#include<math.h>
#include<vector>
#include <cstdlib> 
using namespace std;
long long int binary_to_decimal(string s)
{

    int decimalNumber = 0, i = 0;
    while(i<s.length()){
        
        decimalNumber += ((int)s[i]-48)*pow(2,s.length()-i-1);
        
        i++;
    }
    return decimalNumber;
}

string decimal_to_binary(long long int x , int size ){
    string ret;
    
    for(int i=0;i<size;i++){
        if(x%2==0)ret+='0';
        else ret+='1';
        //cout<<x;
        x=x/2;
    }
    string dum = ret;
    for(int i=0;i<size;i++){
        ret[size-i-1]=dum[i];
    }
    //cout<<endl<<ret<<endl;
    return ret;
}

string read_instructions(string instruction,string &rd,string &rs,string &rt,string &rt3,string &offset,string &sa,string &add,string &imm,int &a,int &b){
    vector<string> v;
    stringstream check(instruction);
        string inter;
        while(getline(check,inter,' ')){
           v.push_back(inter);
        }

if(v[0].compare("add")==0){//add

                  
                     rd=v[1].substr(1,v[1].length()-1);
                     rs=v[2].substr(1,v[2].length()-1);
                     rt=v[3].substr(1,v[3].length()-1);
                        sa="0";
                     a=0;
                     b=0;
        
        }else if(v[0].compare("sub")==0){//sub
                    
                     rd=v[1].substr(1,v[1].length()-1);
                     rs=v[2].substr(1,v[2].length()-1);
                     rt=v[3].substr(1,v[3].length()-1);
                     sa="0";
                    a=0;
                    b=0;
                
        }else if(v[0].compare("lw")==0){
            rs=v[1].substr(1,v[1].length()-1);
            rt=v[2].substr(1,v[2].length()-1);
            
            offset = v[3];
            sa="0";
             a=1;
             b=1;
           

        }else if(v[0].compare("sw")==0){
            rs=v[1].substr(1,v[1].length()-1);
            rt=v[2].substr(1,v[2].length()-1);
            rt3=rt;
            
            sa="0";
            offset = v[3];
            
           b=1;
        }

        else if(v[0].compare("sll")==0){
                    
                    rs="0";
                     rd=v[1].substr(1,v[1].length()-1);
                     rt=v[2].substr(1,v[2].length()-1);
                     sa=v[3];
                     a=0;
                     b=0;
        }else if(v[0].compare("srl")==0){
                    
                    rs="0";
                     rd=v[1].substr(1,v[1].length()-1);
                     rt=v[2].substr(1,v[2].length()-1);
                     sa=v[3];
                     a=0;
                     b=0;
            

        }
        else if(v[0].compare("beq")==0){//beq
                
                     rs=v[1].substr(1,v[1].length()-1);
                     rt=v[2].substr(1,v[2].length()-1);
                     rd="0";
                     imm=v[3];
                     sa="0";
                     a=0;
                     b=0;

            
        }else if(v[0].compare("bne")==0){//bne
                
                     rs=v[1].substr(1,v[1].length()-1);
                     rt=v[2].substr(1,v[2].length()-1);
                     rd="0";
                     imm=v[3];
                     sa="0";
                     a=0;
                     b=0;
                   
        }
        else if(v[0].compare("bgtz")==0){//bgtz
                
                     rs=v[1].substr(1,v[1].length()-1);
                     rd="0";
                     rt="0";
                     imm=v[2];
                     sa="0";
                     a=0;
                     b=0;
                     
        }else if(v[0].compare("bltz")==0){//bltz
                
                     rs=v[1].substr(1,v[1].length()-1);
                     rd="0";
                     rt="0";
                     imm=v[2];
                     sa="0";
                    a=0;
                    b=0;
            
        }
        else if(v[0].compare("j")==0){//jump
                
                     rs="0";
                     rd="0";
                     rt="0";
                     sa="0";
                     add=v[1];
                    a=0;
                    b=0;
        }
        
        return v[0];

}

int alu(string opcode,int op1,int op2,int sa,int &a,int &b){
  int value=0;  
 if(opcode.compare("add")==0){value= op1+op2;a=0;b=0;}
 else if(opcode.compare("sub")==0){value= op1-op2;a=0;b=0;}
 
 else if(opcode.compare("lw")==0){value=op1+op2;a=1;b=0;}
 else if(opcode.compare("sw")==0){value=op1+op2;a=0;b=1;}
 else if(opcode.compare("sll")==0){value=op2*pow(2,sa);a=0;b=0;}
else if(opcode.compare("srl")==0){value=op2/pow(2,sa);a=0;b=0;}


 return value; 
}


int main(){
    ifstream file("input2.txt"); 
    string word, t, q, filename; 
    string ins[128];
    string opcode,rs,rs2,rt2,rt3,rt,rd,rd2,sa,sa2,imm,imm2,address,offset,offset2,base;
    string instruction,instruction2;
    string opcode2;
    int value=0;
    int mux_RegDst=0;
    int mux_RegDst2=0;
    int mux_AluSrc=0;
    int mux_AluSrc2=0;
    int mux_MemRead=0;
    int mux_MemRead2=0;
    int mux_MemWrite=0;
    int mux_MemWrite2=0;
    int mux_MemtoReg=0;
    int mux_MemtoReg2=0;
    int mux_RegWrite=0;
    int mux_RegWrite2=0;
    int mux_PcSrc=0;
    int mux_PcSrc2=0;
    int mux_Zero=0;
    int mux_Zero2=0;
    int write_3=0;
    int forwarding_stage2_rs=0;
    int forwarding_stage2_rt=0;
    int forwarding2_rs=0;
    int forwarding2_rt=0;
    int forwarding_stage3_rs=0;
    int forwarding_stage3_rt=0;
    int forwarding3_rs=0;
    int forwarding3_rt=0;
    int load_forwarding_rs=0;
    int load_forwarding_rt=0;
    int lf_rs=0;
    int lf_rt=0;
    int read_data1=0;
    int read_data2=0;
    int read_data3=0;
    int write_data1=0;
    int write_data2=0;
    int value2=0;
    int read_2=0;
    int write_1=0;
    int write_2=0;
    int pc1=1;
    int bubble[1000]={0};
    int val[1000]={0};
    long long int reg[32]={0};
    int cycle=0;
    int num=0;
    float avg=0;
    reg[8]=9;
    reg[9]=9;

    ins[8]="13";
    ins[9]="14";
    string line;
    int dest[1000];
    int p=0;
    int j=0;
    int k=0;

    while (getline(file,line))
    { 
            
            ins[k]=line;
             
            
        
            
            k++;
        

    } 
    int linked=0;
    while(j<k+4){
        

        if(j<k)
        {
           instruction = ins[j];
       
            cout<<instruction<<endl;
            cout<<"ins "<< j<<" stage0"<<endl;
            
       
       }

         if(p>=4 && j<k+4 && bubble[j-4]==0){ 
            if(mux_RegWrite2==1){
                
                if(mux_MemtoReg2==0){reg[dest[p-4]]=write_1;}
                else{reg[dest[p-4]]=write_2;}   
            }
            cout<<"ins "<< j-4<<" stage4"<<endl;
        } 
        else if(p>=4 && j<k+4 && bubble[j-4]!=0){
            cout<<" stall stage4"<<endl;
        }
      
       if(p>=1 && j<k+1 && instruction2.compare("bubble")!=0) {
            num++;

            opcode=read_instructions(instruction2,rd,rs,rt,rt3,offset,sa,address,imm,mux_RegDst,mux_AluSrc);
            if(opcode.compare("beq")==0){
                if(reg[stoi(rs)]==reg[stoi(rt)]) {pc1=stoi(imm);instruction="bubble";p=j;}
            }
           else if(opcode.compare("bne")==0){
                if(reg[stoi(rs)]!=reg[stoi(rt)]) {pc1=stoi(imm);instruction="bubble";p=j;}
            }
            else if(opcode.compare("bgtz")==0){
                if(reg[stoi(rs)]>0) {pc1=stoi(imm);instruction="bubble";p=j;}
            }
            else if(opcode.compare("bltz")==0){
                if(reg[stoi(rs)]<0) {pc1=stoi(imm);instruction="bubble";p=j;}
            }
           else if(opcode.compare("j")==0){
                
                pc1=stoi(address)-j;
                instruction="bubble";p=j;
           }

           if( p>=2 && mux_RegDst2==0 && stoi(rd2)==stoi(rt) ){
                forwarding2_rt=1;
           }

           if(p>=2 && mux_RegDst2==0 && stoi(rd2)==stoi(rs)){

                forwarding2_rs=1;
           }
           if(p>=3 && dest[p-3]==stoi(rs)){
                forwarding3_rs=1;
           }
           if(p>=3 && dest[p-3]==stoi(rt)){
                forwarding3_rt=1;
           }

           if(p>=2 && mux_RegDst2==1 &&stoi(rt2)==stoi(rs)){

                load_forwarding_rs=1;
           }
           if(p>=2 && mux_RegDst2==1 &&stoi(rt2)==stoi(rt)){
                load_forwarding_rt=1;
           }
           cout<<"ins "<< j-1<<" stage1"<<endl;
            
         }
        else if(p>=1 && j<k+1 && instruction2.compare("bubble")==0){
            cout<<" stall stage1"<<endl;
              bubble[j-1]=1;
        }
         if(p>=2 && j<k+2 && bubble[j-2]==0)
        
        {   
           if(lf_rt==1 || lf_rs==1){
                if(lf_rs==1)forwarding2_rs=1;
                if(lf_rt==1)forwarding2_rt=1;
                cout<<"stall stage2 due to load forwarding"<<endl;
           }
           else{

            if(forwarding_stage2_rs==1){read_data1=val[p-3];}
            else if(forwarding_stage3_rs==1){read_data1=val[p-4];}
            else{read_data1=reg[stoi(rs2)];}


            if(mux_AluSrc2==0){
                if(forwarding_stage2_rt==1) {read_data2=val[p-3];}
                else if(forwarding_stage3_rt==1){read_data2=val[p-4];}
                else read_data2=reg[stoi(rt2)]; 
            }
            else{read_data2=stoi(offset2);}

                if(mux_RegDst2==0){dest[p-2]=stoi(rd2);}
                else{dest[p-2]=stoi(rt2);}

                value=alu(opcode2,read_data1,read_data2,stoi(sa2),mux_MemRead,mux_MemWrite);
                val[p-2]=value;
                cout<<"ins "<< j-2<<" stage2"<<endl;
          } 
            
       }
       else if(p>=2 && j<k+2 && bubble[j-2]!=0){
            
            cout<<" stall stage2"<<endl;
       }
        if(p>=3 && j<k+3 && bubble[j-3]==0){
            mux_RegWrite=0;

            if(mux_MemRead2==0){write_data1=value2;mux_MemtoReg=0;mux_RegWrite=1;}

            else{ write_data2=stoi(ins[value2]);val[p-3]=stoi(ins[value2]);mux_MemtoReg=1;mux_RegWrite=1;}

            if(mux_MemWrite2==1){ins[value2]=to_string(reg[stoi(rt3)]);mux_RegWrite=0;}
           
            cout<<"ins "<< j-3 <<" stage3"<<endl;
        }
        else if(p>=3 && j<k+3 && bubble[j-3]!=0){
           
            cout<<" stall stage3"<<endl;
        }

      
        rs2=rs;
        rt2=rt;
        rd2=rd;
        offset2=offset;
        value2=value;
        read_2=read_data2;
        write_1=write_data1;
        write_2=write_data2;
        opcode2=opcode;
        mux_MemtoReg2=mux_MemtoReg;
        mux_MemWrite2=mux_MemWrite;
        mux_MemRead2=mux_MemRead;
        mux_AluSrc2=mux_AluSrc;
        mux_RegDst2=mux_RegDst;
        mux_RegWrite2=mux_RegWrite;
        sa2=sa;
        instruction2=instruction;
        forwarding_stage2_rs=forwarding2_rs;
        forwarding_stage2_rt=forwarding2_rt;
        forwarding_stage3_rs=forwarding3_rs;
        forwarding_stage3_rt=forwarding3_rt;
        
        forwarding2_rs=0;
        forwarding2_rt=0;
        forwarding3_rs=0;
        forwarding3_rt=0;
        
        if(lf_rs==1 || lf_rt==1)j=j;
        else j=j+pc1;
        if(lf_rs==1 || lf_rt==1)p=p;
        else  p=p+1;
        lf_rs=load_forwarding_rs;
        lf_rt=load_forwarding_rt;
        load_forwarding_rs=0;
        load_forwarding_rt=0;
        pc1=1;
        cycle++;
        cout<<reg[8]<<endl;
        cout<<reg[9]<<endl;
        cout<<reg[10]<<endl;
        cout<<"CYCLE "<<cycle<<endl;

  }     
        for(int i=0;i<32;i++){
            cout<<"reg"<<i<<" = "<<reg[i]<<endl;
        }
       cout<<"SW = "<<ins[8]<<endl;
        avg=(float)num/cycle;
         cout<<"CYCLES = "<<cycle<<endl;
         cout<<"IPC = "<<avg<<endl; 
        return 0;       
}

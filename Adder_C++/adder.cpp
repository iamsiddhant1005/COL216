#include<iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <string.h>
#include<math.h>
#include<vector>
#include <cstdlib> 
using namespace std;

int binary_to_decimal(int s[],int n)
{

    int decimalNumber = 0, i = 0;
    while(i<n){
        
        decimalNumber += s[i]*pow(2,n-i-1);
        
        i++;
    }
    return decimalNumber;
}

void decimal_to_binary( int x , int arr[] ){
    int inv[8];
    
    for(int i=0;i<8;i++){
        if(x%2==0)inv[i]=0;
        else inv[i]=1;
        //cout<<x;
        x=x/2;
    }
    

    for(int i=0;i<8;i++){
        arr[8-i-1]=inv[i];
    }
    //cout<<endl<<ret<<endl;
    
}

void compare(vector<int>v1,vector<int>v2,int &n){
	int pos=0;
	for(int i=0;i<v1.size();i++){
		if(v1[i]!=v2[i]){pos=i;break;}
	}

	if(v1[pos]==0){n=1;}

}

void read_inputs(string instruction[],int op1[],int op2[],int n){
	vector<string> v;
    stringstream check(instruction[n]);
        string inter;
        while(getline(check,inter,' ')){
           v.push_back(inter);
        }
     string a=v[0];
     string b=v[1];   
    for(int i=0;i<a.length();i++){
    	op1[i]=(int)(a[i])-48;
    }
    for(int i=0;i<b.length();i++){
    	op2[i]=(int)(b[i])-48;
    }    
    


}


vector<vector<int>> shift_exponent(int s1[],int exp1[],int frac1[],int s2[],int exp2[],int frac2[],int cycle[],int n,int &guard_bit){
	int pow1=binary_to_decimal(exp1,8);
	int pow2=binary_to_decimal(exp2,8);
	vector<vector<int>> v;
	vector<int>v1,v2;
	v1.push_back(1);
	v2.push_back(1);
	for(int i=0;i<23;i++){
		v1.push_back(frac1[i]);
		v2.push_back(frac2[i]);
	}

	if(pow1>pow2){
		int diff=pow1-pow2;
		
		for(int i=0;i<diff;i++){
			//cout<<"**"<<endl;
			guard_bit=v2[v2.size()-1];
			for(int j=v2.size()-2;j>=0;j--){
				v2[j+1]=v2[j];
			}
			v2[0]=0;
		}

	}
	else if(pow1<pow2){
		int diff=pow2-pow1;
		
		for(int i=0;i<diff;i++){
			guard_bit=v1[v1.size()-1];
			for(int j=v1.size()-2;j>=0;j--){
				v1[j+1]=v1[j];
			}
			v1[0]=0;
		}

	}

	/*for(int i=0;i<v1.size();i++){
		cout<<v1[i];
	}
	cout<<" ";
	for(int i=0;i<v2.size();i++){
		cout<<v2[i];
	}
	cout<<endl;*/
	v.push_back(v1);
	v.push_back(v2);
	cycle[n]=cycle[n]+1;
	return v;
	//cout<<pow1<<" "<<pow2<<endl;
}




vector<int> add_significand(vector<int>v1,vector<int>v2,int cycle[],int n,int sub){
	//cout<<"**"<<endl;
	vector<int>v;
	for(int i=0;i<v1.size()+1;i++){
		v.push_back(0);
	}
	if(sub==0){
		int carry=0;
		for(int i=0;i<v1.size();i++){
			int ans=v1[v1.size()-i-1]+v2[v2.size()-i-1]+carry;
			if(ans>1){
				if(ans==2){
					ans=0;
				
				}
				else{
					ans=1;
				}
				carry=1;
			}
			else{
				carry=0;
			}
		

			v[v1.size()-i]=ans;
		}

		if(carry==1){v[0]=1;}

	}

	else{
		int carry=0;
		for(int i=0;i<v1.size();i++){
			int ans=v1[v1.size()-i-1]-v2[v2.size()-i-1]+carry;
			if(ans<0){
				if(ans==-2){
					ans=0;
				
				}
				else{
					ans=1;
				}
				carry=-1;
			}
			else{
				carry=0;
			}
		

			v[v1.size()-i]=ans;
		}
		if(carry==-1){
			v[0]=1;
		}

	}

	/*for(int i=0;i<v.size();i++){
		cout<<v[i];
	}
	cout<<endl;*/
	cycle[n]=cycle[n]+1;
	return v;

}

void normalize_ans(vector<int>&v,int &pow,int cycle[],int n,int &zero){

	int pos=-1;
	for(int i=0;i<v.size();i++){
		if(v[i]==1){pos=i;break;}
	}

	if(pos==0){
		v.push_back(0);
		for(int j=v.size()-1;j>=0;j--){
				v[j+1]=v[j];
			}
			v[0]=0;
			pow++;
	}
	else if(pos>1 && pos<v.size()){

		for(int i=0;i<pos-1;i++){
			//cout<<"**"<<endl;
			for(int j=1;j<v.size();j++){
				v[j-1]=v[j];
			}
			v[v.size()-1]=0;
			pow--;
		}

	}
	else if(pos==-1){
		zero=1;
	}

	/*for(int i=0;i<v.size();i++){
		cout<<v[i];
	}
	cout<<endl;*/
	cycle[n]=cycle[n]+1;
}


void estimate_ans(vector<int>&v,int cycle[],int n,int guard_bit){
	//cout<<guard_bit<<endl;
	if(v.size()>25|| guard_bit==1){
		//cout<<v.size()<<endl;

		if(guard_bit==1 || v[v.size()-1]==1){
			int carry=1;
			
			for(int i=v.size()-1;i>=0;i--){
				v[i]=v[i]+carry;
				if(v[i]==2){
					v[i]=0;
					carry=1;
				}
				else{
					carry=0;
				}
			}
		}

	}
	else if(v.size()<25){
		int k=25-v.size();
			for(int i=0;i<k;i++){
				v.push_back(0);
			}
	}


	/*for(int i=0;i<v.size();i++){
		cout<<v[i];
	}
	cout<<endl;*/
	cycle[n]=cycle[n]+1;
}



int main(){
	ifstream file("input_11.txt");
	string line;
	string ins[1000];
	int k=0;
	while (getline(file,line))
    { 
            
            ins[k]=line;
            //cout<<ins[k]<<endl;
            k++;
        

    }
    int cycle[k]={0}; 
    int op1[32];
    int op2[32];
    
    int s1[1],exp1[8],frac1[23];
    int s2[1],exp2[8],frac2[23];
    for(int i=0;i<k;i++){
    	int result[32];
    	int guard_bit =0;
    	vector<int>sum_val;
    	read_inputs(ins,op1,op2,i);
    	for(int j=0;j<32;j++){
    		if(j==0)s1[j]=op1[j];
    	    if(j>0 && j<9) exp1[j-1]=op1[j];
    	    if(j>=9) frac1[j-9]=op1[j];
    	}
    	for(int j=0;j<32;j++){
    		if(j==0)s2[j]=op2[j];
    	    if(j>0 && j<9) exp2[j-1]=op2[j];
    	    if(j>=9) frac2[j-9]=op2[j];
    	}
    	int pow1=binary_to_decimal(exp1,8);
		int pow2=binary_to_decimal(exp2,8);
		int zero1 = 1;
		int zero2 = 1;
		for(int i=0;i<23;i++){
			if (frac1[i]==1) {zero1=0; break;}
		}
		for(int i=0;i<23;i++){
			if (frac2[i]==1) {zero2=0; break;}
		}
    	vector<vector<int>> v=shift_exponent(s1,exp1,frac1,s2,exp2,frac2,cycle,i,guard_bit);
    	
   		vector<int> add;
   		int pow_ans;
   		if(pow1>=255 || pow2>=255){
   			if(pow1==255 || pow2==255){
   			 if(pow1==255){
   			 	if(pow2==255){
   			 		if(zero2==0){cout<<"NaN"<<" "<<1<<endl;}
   			 		else{
   			 			if(zero1==0){cout<<"NaN"<<" "<<1<<endl;}
   			 			else{
   			 				if(s1[0]==0 || s2[0]==0) cout<<"Infinity"<<" "<<1<<endl;
   			 				else {cout<<"NaN"<<" "<<1<<endl;}
   			 			}
   			 		}
   			 	}
   			 	else{
   			 		if(zero1==0){cout<<"NaN"<<" "<<1<<endl;}
   			 		else{cout<<"Infinity"<<" "<<1<<endl;}
   			 	}	

   			 }
   			 else{
   			 	if(zero2==0){cout<<"NaN"<<" "<<1<<endl;}
   			 	else{cout<<"Infinity"<<" "<<1<<endl;}
   			 } 
   			 
   			}
   			else cout<<"NaN"<<" "<<1<<endl;
   		}
   		else{
   		if(pow1>=pow2){pow_ans=pow1;}
   		else{pow_ans=pow2;}
   		int s_ans;
   		if(s1[0]==s2[0]){add=add_significand(v[0],v[1],cycle,i,0);s_ans=s1[0];}
   		else{
   			if(pow1>pow2){add=add_significand(v[0],v[1],cycle,i,1);s_ans=s1[0];}
   			else if(pow1<pow2){add=add_significand(v[1],v[0],cycle,i,1);s_ans=s2[0];}
   			else{
   				int sec_large=0;
   				compare(v[0],v[1],sec_large);
   				//cout<<sec_large<<endl;
   				if(sec_large==0){add=add_significand(v[0],v[1],cycle,i,1);s_ans=s1[0];}
   				else{add=add_significand(v[1],v[0],cycle,i,1);s_ans=s2[0];}
   			}
   		}
    	

   		int zero=0;
    	bool bl=false;
    	while(bl!=true){
    		//cout<<pow_ans<<endl;
    		normalize_ans(add,pow_ans,cycle,i,zero);
    		if(zero==1){cout<<0<<" "<<1<<endl;break;}

    		if(pow_ans>254){cout<<"Overflow exception"<<" "<<cycle[i]<<endl;zero=1;break;}
    		else if(pow_ans<1){cout<<"Underflow exception"<<" "<<cycle[i]<<endl;zero=1;break;}
    		estimate_ans(add,cycle,i,guard_bit);

    		if(add[0]==0){bl=true;}
    		//cout<<endl;
    	}
    	if(zero==0){
    		int exp_ans[8];
    		decimal_to_binary(pow_ans,exp_ans);
    		//cout<<pow_ans<<endl;
    		sum_val.push_back(s_ans);
    		for(int j=0;j<8;j++){
    			sum_val.push_back(exp_ans[j]);
    		//cout<<exp_ans[j];
    		}
    		for(int j=2;j<25;j++){
    			sum_val.push_back(add[j]);
    		//cout<<add[j];
    		}
    		cout<<"ANS: ";
    		for(int j=0;j<32;j++){
    			cout<<sum_val[j];
    		}
    		cout<<endl;
    		cout<<"CYCLES  "<<cycle[i];
    		cout<<endl;
    	}
     }
    }
    return 0;
}
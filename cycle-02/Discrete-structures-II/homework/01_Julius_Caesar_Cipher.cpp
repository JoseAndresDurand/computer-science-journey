#include <iostream>
#include <cctype>
using namespace std;

string julioCesarCipher(string L, int k){
    string M="";
    int n = L.size();
    for(int i=0;i<n;i++){
        char c = L[i];
        if(isupper(c)){
            char letraCifrada =((c-'A')+k)%26+'A';
            M += letraCifrada;
        }else if(islower(c)){
            char letraCifrada =((c-'a')+k)%26+'a';
            M += letraCifrada;
        }else{
            M+=c;
        }
    }
    return M;
}


int main(){
    string L;
    int k;
    cout<<"Ingrese la palabra a cifrar"<<endl;
    getline(cin,L);
    cout<<"Ingrese el K posiciones (k>=0): "<<endl;
    cin>>k;
    cout<<"Cifrado con K = "<<k<<" es :"<<julioCesarCipher(L,k)<<endl;
    return 0;
}
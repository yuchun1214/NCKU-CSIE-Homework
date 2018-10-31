#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
template<class T>
class deque : public vector<T>{
public:
    void push_front(T object){vector<T>::insert(vector<T>::begin(),object);}
    void push_back(T object){vector<T>::push_back(object);}
    void pop_back(){ if(vector<T>::size() != 0)vector<T>::pop_back();}
    void pop_front(){ if(vector<T>::size() != 0) vector<T>::erase(vector<T>::begin()); }
    void show(){
        for(typename vector<T>::iterator it = vector<T>::begin();it!=vector<T>::end();it++)
            cout<<*it<<" ";
        cout<<endl;
    }
};
vector<string> InputInstructions(){
    char *pch;
    char str_data[150];
    vector<string> instructions;
    string token;
    cout<<"deque> ";
    scanf("%[^\n]",str_data);
    pch = strtok(str_data," ");
    while(pch != NULL){
        token = pch;
        pch = strtok(NULL," ");
        instructions.push_back(token);
    }
    while ((getchar()) != '\n');
    return instructions;
}
int main(){
    deque<int> dq;
    vector<string> instructions;
    for(int i = 0; i < 50; i++){
        instructions = InputInstructions();
        if(instructions[0] == "push_back") dq.push_back(atoi(instructions[1].c_str()));
        else if(instructions[0] == "push_front") dq.push_front(atoi(instructions[1].c_str()));
        else if(instructions[0] == "pop_back") dq.pop_back();
        else if(instructions[0] == "pop_front") dq.pop_front();
        else if(instructions[0] == "show") dq.show();
        else if(instructions[0] == "exit") exit(0);
        else cout<<"instruction isn't defined"<<endl;
        instructions.clear();
    }
    return 0;
}
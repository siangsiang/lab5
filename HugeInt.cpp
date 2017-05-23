#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<sstream>

using namespace std;

class HugeInt{
 public:
    HugeInt();
    HugeInt(const HugeInt &x);
    HugeInt(string s);
    HugeInt(int x);
    friend ostream& operator<<(ostream &out, HugeInt x);
    friend istream& operator>>(istream &in, HugeInt &x);
    friend HugeInt operator+(HugeInt l, HugeInt r);
    friend HugeInt operator-(HugeInt l, HugeInt r);
    HugeInt& operator=(HugeInt r);
 private:
    vector<int> number;
    void buildstring(const string &s);
};

HugeInt::HugeInt(){
    number.push_back(0);
}
HugeInt::HugeInt(const HugeInt &x){
    number = x.number;
}
HugeInt::HugeInt(string s){
    buildstring(s);
}
void HugeInt::buildstring(const string &s){
    number.clear();
    for(int i=s.size()-1;i>=0;i--)
        number.push_back(s[i]-'0');
}
HugeInt::HugeInt(int x){
    while(x){
      number.push_back(x%10);
	x=x/10;
    }
}
ostream& operator<<(ostream &out, HugeInt x){
    for(int i=x.number.size()-1;i>=0;i--)
    out << x.number[i];
    return out;
}
istream& operator>>(istream &in, HugeInt &x){
    string s;
    in >> s;
    x.buildstring(s);
    return in;
}
HugeInt operator+(HugeInt l, HugeInt r){
    l.number.resize(max(l.number.size(), r.number.size()));
    for(int i=0;i<r.number.size();i++)
        l.number[i] =  l.number[i]+ r.number[i];
    for(int i=1;i<l.number.size();i++){
        if(l.number[i-1] >= 10){
            l.number[i-1] = l.number[i-1]- 10;
            ++ l.number[i];
        }
    }
    if(l.number.back() >= 10) {
        l.number.back() = l.number.back()- 10;
        l.number.push_back(1);
    }
    return l;
}
HugeInt operator-(HugeInt l, HugeInt r){
    l.number.resize(max(l.number.size(), r.number.size()));
    for(int i=0;i<r.number.size();i++)
        l.number[i] = l.number[i]-r.number[i];
    for(int i=0, end = l.number.size()-1 ; i<end ;i++){
        if(l.number[i] < 0){
            l.number[i] = l.number[i]+ 10;
            -- l.number[i+1];
        }
    }
    if(l.number.back() == 0){
        l.number.pop_back();
	}
    return l;
}
HugeInt& HugeInt::operator=(HugeInt r){
    this->number = r.number;
    return *this;
}
	int main(){
	HugeInt x;
	HugeInt y(28825252);
	HugeInt z("314159265358979323846");
	HugeInt result;
	cin >> x;
	result = x+y;
	cout << x << "+" << y << " = " << result << endl;
	result = z - x;
	cout << result << endl;
	return 0;
}


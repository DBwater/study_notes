#include<iostream>
using namespace std;
template<typename T>
class smartptr{
public:
	smartptr(T* ptr=0);
	smartptr(const smartptr& src);
	smartptr& operator= (const smartptr& src);
	T& operator* (){
		if(_ptr){
			return *_ptr;
		}
	}
	T* operator-> (){
		if(_ptr){
			return _ptr;
		}
	}
	~smartptr();
	void print_data(){//不能重载运算符，不然会多算一个指针
		cout<<(*_ptr)<<" "<<*_referece_count<<endl;
	}
private:
	size_t* _referece_count;//引用计数
	T* _ptr;
	void releasecount();
};
template<typename T>
void smartptr<T>::releasecount(){
	if(_ptr){
		//--(*_referece_count);
		if(--(*_referece_count)==0){
			delete _ptr;
			delete _referece_count;
		}
	}
}
template<typename T>
smartptr<T>::smartptr(T* ptr):_ptr(ptr),_referece_count(new size_t){
	if(ptr){
		*_referece_count=1;
	}
	else{
		*_referece_count=0;
	}
}
template<typename T>
smartptr<T>::smartptr(const smartptr& src){
	if(this!=&src){
		_ptr=src._ptr;
		_referece_count = src._referece_count;
		(*_referece_count)++;
	}
}
template<typename T>
smartptr<T>& smartptr<T>::operator= (const smartptr& src){
	if(_ptr == src._ptr){
		*this;
	}
	releasecount();
	_ptr = src._ptr;
	_referece_count=src._referece_count;
	(*_referece_count)++;
	return *this;
}
template<typename T>
smartptr<T>::~smartptr(){
	if(--*(_referece_count)==0){
		delete _ptr;
		delete _referece_count;
	}
}
int main()
{
	smartptr<char>cp1(new char('a'));
	cp1.print_data();
	smartptr<char>cp2(cp1);
	cp2.print_data();
	cp1.print_data();
	smartptr<char>cp3;
	cp3 = cp2;
	cp2.print_data();
	smartptr<char>cp4(new char('b'));
	cp4.print_data();
}

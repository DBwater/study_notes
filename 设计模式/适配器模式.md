# 结构型模式

## 适配器模式（Adapter）
1. 概述：

	将一个类的接口转换成客户希望的另外一个接口。Adapter模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。

2. 适用场景：
	- 已经存在的类的接口不符合我们的需求；
	- 创建一个可以复用的类，使得该类可以与其他不相关的类或不可预见的类（即那些接口可能不一定兼容的类）协同工作；
	- 在不对每一个都进行子类化以匹配它们的接口的情况下，使用一些已经存在的子类。

适配器分为两种，类适配器和对象适配器

## 类适配器
- UML图
![](/home/dbwater/桌面/适配器1.gif)

- 由图中可以看出，Adaptee类没有Request方法，而客户期待这个方法。为了使客户能够使用Adaptee类，提供一个中间环节，即类Adapter类，Adapter类实现了Target接口，并继承自Adaptee，Adapter类的Request方法重新封装了Adaptee的SpecificRequest方法，实现了适配的目的。
- 因为Adapter与Adaptee是继承的关系，所以这决定了这个适配器模式是类的。
- 该适配器模式所涉及的角色包括：
	- 目标（Target）角色：这是客户所期待的接口。因为C#不支持多继承，所以Target必须是接口，不可以是类。
	- 源（Adaptee）角色：需要适配的类。
	- 适配器（Adapter）角色：把源接口转换成目标接口。这一角色必须是类
- 代码实现：

```c++
#include<iostream>
using namespace std;
class Target{
public:
	Target(){}
	virtual ~Target(){}
public:
	virtual void Request()=0;
};
class Adaptee{
public:
	Adaptee(){}
	~Adaptee(){}
public:
	void SpecificRequest(){cout<<"hello world"<<endl;}

};
class Adapter:public Target,private Adaptee{
public:
	Adapter(){}
	~Adapter(){}
public:
	virtual void Request(){
		this->SpecificRequest();
	}
};
int main()
{
	Target* p = new Adapter();
	p->Request();
	return 0;
}

```

## 对象适配器
- UML图
![](/home/dbwater/桌面/适配器2.gif)

- 从图中可以看出：客户端需要调用Request方法，而Adaptee没有该方法，为了使客户端能够使用Adaptee类，需要提供一个包装（Wrapper）类Adapter。这个包装类包装了一个Adaptee的实例，从而将客户端与Adaptee衔接起来。由于Adapter与Adaptee是委派关系，这决定了这个适配器模式是对象的。
- 该适配器模式所涉及的角色包括：
	- 目标（Target）角色：这是客户所期待的接口。目标可以是具体的或抽象的类，也可以是接口。
	- 源（Adaptee）角色：需要适配的类。
	- 适配器（Adapter）角色：通过在内部包装（Wrap）一个Adaptee对象，把源接口转换成目标接口。
- 代码实现

```
#include<iostream>
using namespace std;
class Target{
public:
	Target(){}
	virtual ~Target(){}
public:
	virtual void Request()=0;
};
class Adaptee{
public:
	Adaptee(){}
	~Adaptee(){}
public:
	void SpecificRequest(){cout<<"hello world"<<endl;}
};
class Adapter:public Target{
public:
	Adapter(){
		p = new Adaptee();
	};
	~Adapter(){};
public:
	virtual void Request(){
		p->SpecificRequest();
	}
private:
	Adaptee *p;
};
int main()
{
	Target *p = new Adapter();
	p->Request();
}

```

##两种适配器实现方法的比较
- 类适配器：
	- 用一个具体的Adapter类对Adaptee和Target进行匹配，结果是当我们想要匹配一个类以及所有他的子类的时候，类Adapter将不能胜任。
	- 使得Adapter可以重定义Adaptee的部分行为，因为Adapter是Adaptee的一个子类。
	- 仅仅引用了一个对象，并不需要额外的指针以间接得到Adapteee。
	- 类适配器采用“多继承”的实现方式，带来了不良的高耦合，所以一般不推荐使用。
- 对象适配器：
	- 允许一个Adapter与多个Adaptee（Adaptee本身和他的所有子类）同时工作，Adaptee也可以一次给所有的Adaptee添加功能。
	- 使得重定义Adaptee的行为比较困难。这就需要生成Adaptee的子类并且使得Adapter引用这个子类而不是引用Adaptee本身


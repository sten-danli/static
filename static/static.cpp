//static 和 const的详解；
#include <iostream>
using namespace std;
class Test
{
	friend void Show(Test&t);
private:
	int data;
	static int count;
public:
	Test(int d = 0) :data(d)
	{
		count++;
	}
	~Test()
	{
		count--;
	}

//const举例详解；
public:void list()//普通成员方法；
	{
	data = 988;
	cout << "This is list()" << endl;
	}

public:void list()const//常方法；
{
	//data = 899;因const所以不能修改成员变量；
	cout << "This is list()const" << endl;
}
	//一个函数的const即可以修饰参数也可以修饰函数，还可以修饰返回值。
	/*例如：void func（const Test&t）这里面const的作用主要是该参数不能在其函数内部该引用对象进行成员的修改，
	这主要是为了保护参数。
	而void func（const Test&t）const 这里有在函数后加了一个const，那么这个const又起了什么作用呢？
	它所修饰的方法叫做常量方法，常方法是限定该方法不能去改变整个类的数据成员，也就是常方法指定的是这个方法是常性的，我不能再方法的内部或者函数的内部
	对数据成员进行任何的数据修改，这就是const的表面意思。其根本理解是这样的：

	void list() 实际内部解析是这样的: void list(Test * const this)

	和带有尾部带有const函数的内部解析：

	void list()const 实际内部解析是这样的: void list(const Test * const this)

	第二函数的const是修饰谁的呢？
	这个const写在了函数的后面，这个const最终是加到了Test前面，如下：

	1.	void list(const Test * const this)
	他和
	2.	void list(Test * const this)

	的区别是：void list(Test *const this) const只封锁this指针指向谁不允许改变，但this所指的的对象内容是可以修改的，所以我们
	可以修改成员对象的值，但是函数后加了const如下：

		void list()const = 	void list(const Test * const this)
	const最终要封锁的是*this为常量，也就是他所指的对象为常量，这样对象内的数据都为常量不可修改。所以我们说常方法不能修改成员数
	据，究其根本是应为const封锁的是*this为常量。（const Test内隐藏着this指针，所以const Test就等于 const *this。
	*/
	
//static详解；
public: //普通方法是可以访问静态成员和普通成员函数的，但是静态函数只能访问静态变量和静态成员函数；
		//例如在如下函数前加上Static修饰后，static void Show1()，此时函数调动失败，因为他加
		//上static修饰后这个函数就只能访问静态成员函数了，而不能访问普通变量，为什么是这样呢：
/*它们本质主要在这里，普同的方法在改写的时候，一定会在他的内部默认的或是隐藏着插入一个以自身类型命
 * 名的const的this指针，这是我们改写方法的时候要注意的，普通的成元方法一定会在这里又一个this的
 * 指针，就像这样：void Show() = void Show(Test * const this)，但是一旦加上static后静态之后，
 * 静态的变量和静态的方法都有一个特点，他属于为其对象共享，所以我们静态方法就不再有this的指针，这就
 *是静态函数的特点，而普通函数的特点是：
 * 1.该函数能访问类生命的私有部分。
 * 2.该函数位于类作用域中。
 * 3.该函数必须经由一个对象去激活（有一个this指针）
 * 而静态函数遵循普通函数的前两点，我们通常把静态函数它称为静态成员，但该函数不再有一个对象去激活，
 * 因为他没有指针，所以说静态方法和普通方法的最大区别就在于静态方法没有tihs指针，所以用静态函数去
 * 访问有指针的普通函数和数据是不行的.
 *
	 */
	 void Show1(Test d)//普通方法是可以访问静态函数和成员数据变量，但是如果加上static就只能访问静态函数和变量的count；
	{
		 data = d.data;
		 cout << data << endl;
		 cout << Test::count;
	}
};
void Show(Test& t)
{
	t.data = 999;
	cout << "t.data= " << t.data << endl;
	cout << "count= " << Test::count << endl;
}
//init static count;
int Test::count = 0;
int main()
{
	Test t(100);
	Test t1(999);
	t1.Show1(t1);
}

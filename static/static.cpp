#include <iostream>
using namespace std;
class Test
{
	friend void Show(Test&);
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
public: //普通方法是可以访问静态成员和普通成员函数的，但是静态函数只能访问静态变量和静态成员函数；
		//例如在如下函数前加上Static修饰后，static void Show1()，此时函数调动失败，因为他加
		//上static修饰后这个函数就只能访问静态成员函数了，而不能访问普通变量，为什么是这样呢：
/*它们本质主要在这里，普同的方法在改写的时候，一定会在他的内部默认的或是隐藏着插入一个以自身类型命
 * 名的const的this指针，这是我们改写方法的时候要注意的，普通的成元方法一定会在这里又一个this的
 * 指针，就像这样：void Show(Test * const this)，但是一旦加上static后静态之后，静态的变量和
 * 静态的方法都有一个特点，他属于为其对象共享，所以我们静态方法就不再有this的指针，这就是静态函数的
 * 特点，而普通函数的特点是：
 * 1.该函数能访问类生命的私有部分。
 * 2.该函数位于类作用域中。
 * 3.该函数必须经由一个对象去激活（有一个this指针）
 * 而静态函数遵循普通函数的前两点，我们通常把静态函数它称为静态成员，但该函数不再有一个对象去激活，
 * 因为他没有指针，所以说静态方法和普通方法的最大区别就在于静态方法没有tihs指针，所以用静态函数去
 * 访问有指针的普通函数和数据是不行的，
 *
	 */
	void Show1()
	{
		cout << data;
		cout << count;
	}
};
void Show(Test& t)
{
	cout << "t.data= " << t.data << endl;
	cout << "count= " << Test::count << endl;
}
//init static count;
int Test::count = 0;
int main()
{
	Test t(100);
	Test t1(200);
	Show(t);
}

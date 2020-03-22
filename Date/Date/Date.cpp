#include<iostream>
using namespace std;


class Date
{
public:
	int GetMonthDays(int year, int month)
	{
		static int monthDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int days = monthDays[month];
		if (month == 2 && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0))
		{
			days = 29;
		}
		return days;
	}
	Date(int year = 1, int month = 0, int day = 0)
	{
		if (year >= 0
			&& month > 0 && month < 13
			&& day > 0 && day < GetMonthDays(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
			cout << "非法日期" << endl;
	}

	// 拷贝构造函数可以不写
	// d2(d1)
	//Date(const Date& d);

		// 赋值运算符重载
		// d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_year = d._year;
		}
		return *this;
	}
	// 析构函数可以不写
	//~Date();
	// 日期+=天数
	Date& operator+=(int day)
	{	
		if (day < 0)
		{
			*this -= -day;
			return *this;
		}
		_day += day;
		while (day > GetMonthDays(_year, _month))
		{
			_day -= GetMonthDays(_year, _month);
			_month++;
			if (_month == 13)
			{
				_year++;
				_month = 1;
			}
		}
		return *this;
	}
	// 日期+天数
	Date operator+(int day)
	{
		Date ret(*this);//*this 就是d，ret相当于d1的拷贝
		/*ret._day += day;
		while (ret._day > GetMonthDays(ret._year, ret._month))
		{
			ret._day -= GetMonthDays(ret._year, ret._month);
			ret._month++;
			if (ret._month == 13)
			{
				ret._year++;
				ret._month = 1;
			}
		}*/
		ret.operator+=(day);
		return ret;
	}
	// 日期-=天数
	Date& operator-=(int day)
	{	
		if (day < 0)
		{
			*this -= -day;
			return *this;
		}
		_day -= day;
		while (_day <= 0)
		{
			_month--;
			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
			_day += GetMonthDays(_year, _month);
		}
		return *this;
	}
	// 日期-天数
	Date operator-(int day)
	{
		Date ret(*this);
		ret.operator-=(day);
		return ret;
	}
	// 前置++
	Date& operator++()
	{
		*this += 1;
		return *this;
	}
	// 后置++
	Date operator++(int)
	{
		Date ret(*this);
		*this += 1;
		return ret;
	}
	// 后置--
	Date operator--(int)
	{
		Date ret(*this);
		*this -= 1;
		return ret;
	}
	// 前置--
	Date& operator--()
	{
		*this -= 1;
		return *this;
	}

	// >运算符重载
	bool operator>(const Date& d)
	{
		if ((_year > d._year) || (_year == d._year && _month > d._month) || (_year == d._year && _month == d._month && _day > d._day))
		{
			return true;
		}
		return false;
	}
	// ==运算符重载
	bool operator==(const Date& d)
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}
	// >=运算符重载
	bool operator >= (const Date& d)
	{
		return *this > d || *this == d;
	}

	// <运算符重载
	bool operator < (const Date& d)
	{
		return !(*this >= d);
	}
	// <=运算符重载
	bool operator <= (const Date& d)
	{
		return !(*this > d);
	}
	// !=运算符重载
	bool operator != (const Date& d)
	{
		return !(*this == d);
	}
	// 日期-日期 返回天数
	int operator - (const Date& d)
	{
		int falg = -1;
		Date min = *this;
	    Date max = d;

		if (*this > d)
		{
			falg = 1;
			min = d;
			max = *this;
		}
		int n = 0;
		while (min != max)
		{
			++n;
			++min;
		}
		return n*falg;

		
	}
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};



int main()
{
	Date d1(2020, 3, 12);
	d1.Print();
	cout << "--------------------------" << endl;

	Date d2 = d1.operator+(10);
	d2.Print();
	d1.Print();
	cout << "--------------------------" << endl;

	Date d3 = d1.operator+=(10);
	d3.Print();
	d1.Print();
	cout << "--------------------------" << endl;

	Date d4 = d1.operator-(10);
	d4.Print();
	d1.Print();
	cout << "--------------------------" << endl;

	Date d5 = d1.operator-=(10);
	d5.Print();
	d1.Print();
	cout << "--------------------------" << endl;
	Date d6 = d1++;
	d6.Print();
	Date d7 = ++d2;
	d7.Print();
	cout << "--------------------------" << endl;

	Date d8(219, 4, 19);
    Date d9(2020, 5, 19);
	cout << (d8 != d9) << endl;
	cout << "--------------------------" << endl;

	Date d10(2020, 3, 9);
	Date d11(2020, 4, 10);
	cout << d10 - d11 << endl;
	cout << d11 - d10 << endl;

	return 0;
}


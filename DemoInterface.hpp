//          Copyright John R. Bandela 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "cross_compiler_interface/cross_compiler_interface.hpp"
#include <string>

// Use cross_function without namespace to shorten code
using cross_compiler_interface::cross_function;


// A Base class to show you can inherit an interface


template<class T> // All interfaces take a bool template parameter

// All interfaces need to derive from define_interface passing in the bool parameter, and the number of functions
struct BaseInterface:public cross_compiler_interface::define_interface<T>{

	// To declare a function in the interface use cross_function
	// it takes the BaseInterface,the 0 based id of the function (starting from 0 to the number of functions - 1,
	// and the signature - same as you would use for std::function;
	cross_function<BaseInterface,0,std::string()> hello_from_base;

	// The interface needs a templated constructor that takes t and passes it to each cross_function constructor
	// also needs to pass the t to the define_iterface base, define_interface typedefs base_t to itself
	BaseInterface():hello_from_base(this){}
};

// This is an interface that we will pass into a function
template<class T>
struct IGetName:public cross_compiler_interface::define_interface<T>{
	cross_function<IGetName,0,std::string()> get_name;

	IGetName():get_name(this){}

};

template<class T> struct DemoInterface:public cross_compiler_interface::define_interface<T,BaseInterface>{

	// Pass in an int and return an int
	cross_function<DemoInterface,0,int(int)> plus_5;

	// Same as above with double
	cross_function<DemoInterface,1,double(double)> times_2point5;

	// Manipulate a reference
	cross_function<DemoInterface,2,void(int&)> double_referenced_int;

	// Receive a string and get an int
	cross_function<DemoInterface,3,std::size_t(std::string)> count_characters;

	// String as parameter and return
	cross_function<DemoInterface,4,std::string(std::string)> say_hello;

	// An exception thrown by STL
	cross_function<DemoInterface,5,void(std::string)> use_at_out_of_range;

	// Another exception thrown by cross_compiler_interface
	cross_function<DemoInterface,6,void()> not_implemented;

	// Return a vector<string>
	cross_function<DemoInterface,7,std::vector<std::string>(std::string)> split_into_words;

	// Use another interface
	cross_function<DemoInterface,8,std::string(cross_compiler_interface::use_interface<IGetName>)> say_hello2;

	cross_function<DemoInterface,9,std::pair<int,std::string> (std::vector<std::string> v,int pos)> get_string_at;



	// Initialize the base class (base_t) and all the functions
	DemoInterface():
		plus_5(this),times_2point5(this),double_referenced_int(this),
		count_characters(this),say_hello(this),use_at_out_of_range(this),not_implemented(this),split_into_words(this),say_hello2(this),
		get_string_at(this){}
};
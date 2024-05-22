#include <iostream>
#include <sstream>
using namespace std;
 
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

struct base {
	virtual ~base() = default;

	void print_int() {
		print_warning();
		print_int(1);
	}

	virtual void print_int(int a){
		cout << "print_int base : "<<a<<endl;
	}

	virtual void print_warning() {
		
	}
};
 
struct child : base {
	~child() = default;

	void print_int() {
		print_warning();
		print_int(2);
	}

	void print_int(int a) override {
		cout<<"print_int child : "<<a<<endl;
	}

	void print_warning() override {
		cout << WARNING_MESSAGE << endl;
	}

	inline static std::string WARNING_MESSAGE = "default assigment takes place, expecting replacing : 1 on 2";
};

struct base_original {
	virtual ~base_original() = default;

	virtual void print_int(int a = 1) {
		cout << "print_int base : " << a << endl;
	}
};

struct child_original : base_original {
	~child_original() = default;

	void print_int(int a = 2) override {
		cout << "print_int child : " << a << endl;
	}
};

//https://gist.github.com/rudolfovich/9fc5bdd110d543b46afdbdd845a82377
class StdIOStreamRedirect
{
	std::streambuf* coutbuf_;
	std::ostringstream out_;
public:
	StdIOStreamRedirect()
		: coutbuf_(std::cout.rdbuf())
	{
		std::cout.rdbuf(out_.rdbuf());
	}

	~StdIOStreamRedirect()
	{
		std::cout.rdbuf(coutbuf_);
	}

	std::string output() { return out_.str(); }
};

TEST_CASE("testing size_t predicates with ctor") {
	StdIOStreamRedirect redirect;
	SUBCASE("base child empty") {
		base* p = new child;
		p->print_int();
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			base_original* po = new child_original;
			po->print_int();
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(child::WARNING_MESSAGE + "\n" + messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("base child 1") {
		base* p = new child;
		p->print_int(1);
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			base_original* po = new child_original;
			po->print_int(1);
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("base child 2") {
		base* p = new child;
		p->print_int(2);
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			base_original* po = new child_original;
			po->print_int(2);
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("base child 10") {
		base* p = new child;
		p->print_int(10);
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			base_original* po = new child_original;
			po->print_int(10);
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("base base empty") {
		base* p = new base;
		p->print_int();
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			base_original* po = new base_original;
			po->print_int();
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("base base 1") {
		base* p = new base;
		p->print_int(1);
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			base_original* po = new base_original;
			po->print_int(1);
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("base base 2") {
		base* p = new base;
		p->print_int(2);
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			base_original* po = new base_original;
			po->print_int(2);
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("base base 10") {
		base* p = new base;
		p->print_int(10);
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			base_original* po = new base_original;
			po->print_int(10);
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("child child empty") {
		child* p = new child;
		p->print_int();
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			child_original* po = new child_original;
			po->print_int();
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(child::WARNING_MESSAGE + "\n" + messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("child child 1") {
		child* p = new child;
		p->print_int(1);
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			child_original* po = new child_original;
			po->print_int(1);
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("base base 2") {
		child* p = new child;
		p->print_int(2);
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			child_original* po = new child_original;
			po->print_int(2);
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(messageOriginal, message);
			delete po;
		}
		delete p;
	}
	SUBCASE("base base 10") {
		child* p = new child;
		p->print_int(10);
		auto message = redirect.output();
		{
			StdIOStreamRedirect redirectForOriginal;
			child_original* po = new child_original;
			po->print_int(10);
			auto messageOriginal = redirectForOriginal.output();
			CHECK_EQ(messageOriginal, message);
			delete po;
		}
		delete p;
	}
}
#include <iomanip>
#include <iostream>
using namespace std;

typedef const char* CHARPTR;

class mystr {
public:
	mystr(const char* data = nullptr)
		: data_(nullptr)
		, size_(0)
	{
		cout << "dflt c-tor : 0x" << hex << this << dec << endl;
		if (!data) return;

		size_ = strlen(data);
		data_ = new char[size_];
		memcpy(data_, data, size_);
	}
	~mystr() {
		cout << "dflt d-tor : 0x" << hex << this << dec << endl;
		delete[] data_;
	}
	mystr(const mystr& copy)
		: data_(nullptr)
		, size_(0)
	{
		cout << "copy c-tor : 0x" << hex << this << dec << endl;
		copy_internal(copy);
	}
	mystr& operator=(const mystr& copy) {
		return copy_internal(copy);
	}
	mystr(mystr&& copy) noexcept
		: data_(nullptr)
		, size_(0)
	{
		cout << "move c-tor : 0x" << hex << this << dec << endl;
		move_internal(std::move(copy));
	}
	mystr& operator=(mystr&& copy) noexcept {
		return move_internal(std::move(copy));
	}
	const char* data() const { return data_; }
	const size_t size() const { return size_; }

	operator CHARPTR() const {
		return data_;
	}
private:
	size_t  size_;
	char* data_;

	mystr& copy_internal(const mystr& copy) {
		if (this == &copy) return *this;

		delete[] data_;
		data_ = nullptr;

		size_ = copy.size_;
		if (!size_) return *this;

		data_ = new char[size_];
		memcpy(data_, copy.data_, size_);

		return *this;
	}

	mystr& move_internal(mystr&& copy) noexcept {
		if (this == &copy) return *this;

		data_ = copy.data_;
		size_ = copy.size_;

		copy.data_ = nullptr;

		return *this;
	}
};

int main() {
	{
		mystr t1 = mystr("copy c-tor test");
		mystr t2 = std::move(t1);

		mystr t3;
		t3 = std::move(t2);

		mystr t4 = t3;
		mystr t5;

		t5 = t4;

		cout << (CHARPTR)t5 << endl;
	}
	return cin.get(), 0;
};
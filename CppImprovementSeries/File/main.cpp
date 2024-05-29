#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define RUN_TESTS

#include "Application.h"
#include "Exception.h"

#include <filesystem>

TEST_CASE("testing modes") {
	{
		Mode m = Mode::Open;
		CHECK(hasMode(m, Mode::Open));
		CHECK_FALSE(hasMode(m, Mode::Trunc));
		CHECK_FALSE(hasMode(m, Mode::Ate));
		CHECK_FALSE(hasMode(m, Mode::Binary));
		CHECK_FALSE(hasMode(m, Mode::Create));
	}
	{
		Mode m = Mode::Trunc | Mode::Ate;
		CHECK(hasMode(m, Mode::Trunc));
		CHECK(hasMode(m, Mode::Ate));
		CHECK_FALSE(hasMode(m, Mode::Binary));
		CHECK_FALSE(hasMode(m, Mode::Create));
		CHECK_FALSE(hasMode(m, Mode::Open));
	}
	{
		Mode m = Mode::Create | Mode::Open | Mode::Binary;
		CHECK(hasMode(m, Mode::Create));
		CHECK(hasMode(m, Mode::Open));
		CHECK(hasMode(m, Mode::Binary));
		CHECK_FALSE(hasMode(m, Mode::Ate));
		CHECK_FALSE(hasMode(m, Mode::Trunc));
	}
	{
		Mode m = Mode::Trunc | Mode::Create | Mode::Open | Mode::Binary;
		CHECK(hasMode(m, Mode::Create));
		CHECK(hasMode(m, Mode::Open));
		CHECK(hasMode(m, Mode::Binary));
		CHECK(hasMode(m, Mode::Trunc));
		CHECK_FALSE(hasMode(m, Mode::Ate));
	}
	{
		Mode m = Mode::Ate | Mode::Trunc | Mode::Create | Mode::Open | Mode::Binary;
		CHECK(hasMode(m, Mode::Create));
		CHECK(hasMode(m, Mode::Open));
		CHECK(hasMode(m, Mode::Binary));
		CHECK(hasMode(m, Mode::Trunc));
		CHECK(hasMode(m, Mode::Ate));
	}
}

TEST_CASE("testing file creation and opening with different modes") {
	auto filename = "test.txt";
	if (std::filesystem::exists(filename)) {
		std::filesystem::remove(filename);
	}
	File f;
	CHECK_THROWS_AS(f.open(filename, Mode::Open), FileException);
	CHECK_FALSE(std::filesystem::exists(filename));
	CHECK_THROWS_AS(f.open(filename, Mode::Ate), FileException);
	CHECK_FALSE(std::filesystem::exists(filename));
	CHECK_THROWS_AS(f.open(filename, Mode::Binary), FileException);
	CHECK_FALSE(std::filesystem::exists(filename));

	f.open(filename, Mode::Create);
	CHECK(std::filesystem::exists(filename));
	std::string toWrite("123");
	f.write(toWrite.c_str(), toWrite.length());
	CHECK_EQ(f.getLength(), toWrite.length());
	f.seek(0);
	std::string buff(toWrite.length(), ' ');
	f.read(buff.data(), buff.length());
	CHECK_EQ(buff, toWrite);
	f.close();
	f.open(filename, Mode::Trunc);
	CHECK_EQ(f.getLength(), 0);
	f.close();
	
	CHECK_THROWS_AS(f.open(filename, Mode::Create), FileException);
	
	std::filesystem::remove(filename);
	CHECK_THROWS_AS(f.open(filename, Mode::Trunc), FileException);
	CHECK_FALSE(std::filesystem::exists(filename));
}

TEST_CASE("testing open and ate mode") {
	auto filename = "test.txt";
	if (std::filesystem::exists(filename)) {
		std::filesystem::remove(filename);
	}
	File f(filename, Mode::Create);
	std::string toWrite("abcd");
	f.write(toWrite.c_str(), toWrite.length());
	CHECK_EQ(f.getLength(), toWrite.length());
	f.close();

	f.open(filename, Mode::Open);
	CHECK_EQ(f.getPosition(), 0);
	std::string buff(toWrite.length(), ' ');
	f.read(buff.data(), buff.length());
	CHECK_EQ(buff, toWrite);
	f.close();

	f.open(filename, Mode::Ate);
	CHECK_EQ(f.getPosition(), f.getLength());
	f.close();
	std::filesystem::remove(filename);
}

int main()
{
#ifdef RUN_TESTS
	doctest::Context context;
	context.run();
#endif // RUN_TESTS

	Application app;
	app.run();
}

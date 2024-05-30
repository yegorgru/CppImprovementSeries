#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define RUN_TESTS

#include "Application.h"
#include "Exception.h"
#include "File.h"
#include "DataFile.h"

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

class Messages {
public:
	inline static const std::string TooLongName = "Too long name provided. Resized to 5 characters";
	inline static const std::string EnterFilename = "Enter filename";
	inline static const std::string OpenSuccess = "Open successfully";
	inline static const std::string CloseSuccess = "Close successfully";
	inline static const std::string EnterPosition = "Enter position";
	inline static const std::string SeekSuccess = "Seek successfully";
	inline static const std::string EnterCharactersCount = "Enter characters count";
	inline static const std::string WriteSuccess = "Write successfully";
	inline static const std::string AppendSuccess = "Append successfully";
	inline static const std::string InputInt = "Input int";
	inline static const std::string InputString = "Input string";
	inline static const std::string InputDouble = "Input double";
	inline static const std::string InputIndex = "Input index";
	inline static const std::string InputDataStruct = "Input data struct in format name a b c";
};

class ErrorMessages {
public:
	inline static const std::string NotNegativeValue = "Value should be greater or equal to 0!";
	inline static const std::string IncorrectDataInput = "Incorrect data input";
	inline static const std::string IncorrectIntInput = "Incorrect int input";
	inline static const std::string IncorrectDoubleInput = "Incorrect double input";
};

int main()
{
#ifdef RUN_TESTS
	doctest::Context context;
	context.run();
#endif // RUN_TESTS

	File file;
	DataFile dataFile;
	View view;
	Application app(view);

	auto getInt = [&view](const std::string& message, bool positiveCheck) {
		view.showMessage(message);
		auto inputStream = std::istringstream(view.getStringLine());
		int input = 0;
		bool result = (inputStream >> input && inputStream.eof());
		if (inputStream.fail() || !result) {
			throw InputException(ErrorMessages::IncorrectIntInput);
		}
		if (positiveCheck && input < 0) {
			throw InputException(ErrorMessages::NotNegativeValue);
		}
		return input;
	};

	auto getDouble = [&view](const std::string& message) {
		view.showMessage(message);
		auto inputStream = std::istringstream(view.getStringLine());
		double input = 0;
		bool result = (inputStream >> input && inputStream.eof());
		if (inputStream.fail() || !result) {
			throw InputException(ErrorMessages::IncorrectDoubleInput);
		}
		return input;
	};

	auto getData = [&view](const std::string& message) {
		view.showMessage(message);
		DataFile::Data data;
		std::istringstream is(view.getStringLine());
		std::string name;
		bool result = (is >> name >> data.a >> data.b >> data.c) && (is.eof());
		if (is.fail() || !result) {
			throw InputException(ErrorMessages::IncorrectDataInput);
		}
		if (name.length() > DataFile::Data::NameSize) {
			view.showMessage(Messages::TooLongName);
			name.resize(DataFile::Data::NameSize);
		}
		std::strcpy(data.name.data(), name.c_str());
		data.name.back() = '\0';
		return data;
	};

	app.registerMenuItem(0, "Exit", [&app]() {app.setExitFlag(); });
	app.registerMenuItem(1, "Create plain file", [&view, &file]() {		
		view.showMessage(Messages::EnterFilename);
		auto name = view.getStringLine();
		file.open(name, Mode::Create);
		view.showMessage(Messages::OpenSuccess); 
	});
	app.registerMenuItem(2, "Truncate plain file", [&view, &file]() {
		view.showMessage(Messages::EnterFilename);
		auto name = view.getStringLine();
		file.open(name, Mode::Trunc);
		view.showMessage(Messages::OpenSuccess);
	});
	app.registerMenuItem(3, "Open plain file", [&view, &file]() {
		view.showMessage(Messages::EnterFilename);
		auto name = view.getStringLine();
		file.open(name, Mode::Open);
		view.showMessage(Messages::OpenSuccess);
	});
	app.registerMenuItem(4, "Open plain file in ate mode", [&view, &file]() {
		view.showMessage(Messages::EnterFilename);
		auto name = view.getStringLine();
		file.open(name, Mode::Ate);
		view.showMessage(Messages::OpenSuccess);
	});
	app.registerMenuItem(5, "Open plain file in binary mode", [&view, &file]() {
		view.showMessage(Messages::EnterFilename);
		auto name = view.getStringLine();
		file.open(name, Mode::Open | Mode::Binary);
		view.showMessage(Messages::OpenSuccess);
	});
	app.registerMenuItem(6, "Close plain file", [&view, &file]() {
		file.close();
		view.showMessage(Messages::CloseSuccess);
	});
	app.registerMenuItem(7, "Seek plain file", [&view, &file, &getInt]() {
		auto pos = getInt(Messages::EnterPosition, true);
		file.seek(pos);
		view.showMessage(Messages::SeekSuccess);
	});
	app.registerMenuItem(8, "Get position plain file", [&view, &file]() {
		auto pos = file.getPosition();
		view.showMessage(pos);
	});
	app.registerMenuItem(9, "Get length plain file", [&view, &file]() {
		auto length = file.getLength();
		view.showMessage(length);
	});
	app.registerMenuItem(10, "Read int from plain file", [&view, &file]() {
		int number;
		file >> number;
		view.showMessage(number);
	});
	app.registerMenuItem(11, "Read string from plain file", [&view, &file]() {
		std::string str;
		file >> str;
		view.showMessage(str);
	});
	app.registerMenuItem(12, "Read double from plain file", [&view, &file]() {
		double d;
		file >> d;
		view.showMessage(d);
	});
	app.registerMenuItem(13, "Write int to plain file", [&view, &file, &getInt]() {
		auto input = getInt(Messages::InputInt, false);
		file << input;
		view.showMessage(Messages::WriteSuccess);
	});
	app.registerMenuItem(14, "Write string to plain file", [&view, &file]() {
		view.showMessage(Messages::InputString);
		auto input = view.getStringLine();
		file << input;
		view.showMessage(Messages::WriteSuccess);
	});
	app.registerMenuItem(15, "Write double to plain file", [&view, &file, &getDouble]() {
		auto input = getDouble(Messages::InputDouble);
		file << input;
		view.showMessage(Messages::WriteSuccess);
	});
	app.registerMenuItem(16, "Read binary int from plain file", [&view, &file]() {
		int number;
		file.read(reinterpret_cast<char*>(&number), sizeof(number));
		view.showMessage(number);
		});
	app.registerMenuItem(17, "Read binary string from plain file", [&view, &file, &getInt]() {
		auto count = getInt(Messages::EnterCharactersCount, true);
		std::string str(count, ' ');
		file.read(str.data(), count);
		view.showMessage(str);
		});
	app.registerMenuItem(18, "Read binary double from plain file", [&view, &file]() {
		double d;
		file.read(reinterpret_cast<char*>(&d), sizeof(d));
		view.showMessage(d);
		});
	app.registerMenuItem(19, "Write binary int to plain file", [&view, &file, &getInt]() {
		auto input = getInt(Messages::InputInt, false);
		file.write(reinterpret_cast<char*>(&input), sizeof(input));
		view.showMessage(Messages::WriteSuccess);
		});
	app.registerMenuItem(20, "Write binary string to plain file", [&view, &file]() {
		view.showMessage(Messages::InputString);
		auto input = view.getStringLine();
		file.write(input.data(), input.size());
		view.showMessage(Messages::WriteSuccess);
		});
	app.registerMenuItem(21, "Write binary double to plain file", [&view, &file, &getDouble]() {
		auto input = getDouble(Messages::InputDouble);
		file.write(reinterpret_cast<char*>(&input), sizeof(input));
		view.showMessage(Messages::WriteSuccess);
	});
	app.registerMenuItem(22, "Create data file", [&view, &dataFile]() {
		view.showMessage(Messages::EnterFilename);
		auto name = view.getStringLine();
		dataFile.open(name, Mode::Create);
		view.showMessage(Messages::OpenSuccess);
		});
	app.registerMenuItem(23, "Truncate data file", [&view, &dataFile]() {
		view.showMessage(Messages::EnterFilename);
		auto name = view.getStringLine();
		dataFile.open(name, Mode::Trunc);
		view.showMessage(Messages::OpenSuccess);
	});
	app.registerMenuItem(24, "Open data file", [&view, &dataFile]() {
		view.showMessage(Messages::EnterFilename);
		auto name = view.getStringLine();
		dataFile.open(name, Mode::Open);
		view.showMessage(Messages::OpenSuccess);
	});
	app.registerMenuItem(25, "Close data file", [&view, &dataFile]() {
		dataFile.close();
		view.showMessage(Messages::CloseSuccess);
	});
	app.registerMenuItem(26, "Read data", [&view, &dataFile, &getInt]() {
		DataFile::Data data;
		auto idx = getInt(Messages::InputIndex, true);
		dataFile.read(data, idx);
		view.showMessage("a: ", data.a, ", b: ", data.b, ", c: ", data.c, ", name: ", data.name.data());
	});
	app.registerMenuItem(27, "Set data", [&view, &dataFile, &getInt, &getData]() {
		auto data = getData(Messages::InputDataStruct);
		auto idx = getInt(Messages::InputIndex, true);
		dataFile.write(data, idx);
		view.showMessage(Messages::WriteSuccess);
	});
	app.registerMenuItem(28, "Append data", [&view, &dataFile, &getData]() {
		auto data = getData(Messages::InputDataStruct);
		dataFile.append(data);
		view.showMessage(Messages::AppendSuccess);
	});
	app.registerMenuItem(29, "Get data count", [&view, &dataFile]() {
		auto length = dataFile.getDataCount();
		view.showMessage(length);
	});

	app.run();
}
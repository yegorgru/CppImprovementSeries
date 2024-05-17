#include "Application.h"
#include "Exception.h"

#include <sstream>

void Application::run() {
	static auto createFileHandler = [this]() {
		mView.showMessage(Messages::EnterFilename);
		auto name = mView.getStringLine();
		mFile.open(name, File::Mode::Trunc);
		mView.showMessage(Messages::OpenSuccess);
	};
	static auto openFileHandler = [this]() {
		mView.showMessage(Messages::EnterFilename);
		auto name = mView.getStringLine();
		mFile.open(name, File::Mode::Open);
		mView.showMessage(Messages::OpenSuccess);
	};
	static auto closeFileHandler = [this]() {
		mFile.close();
		mView.showMessage(Messages::CloseSuccess);
	};
	static auto seekFileHandler = [this]() {
		auto pos = getInt(Messages::EnterPosition, true);
		mFile.seek(pos);
		mView.showMessage(Messages::SeekSuccess);
	};
	static auto getPositionFileHandler = [this]() {
		auto pos = mFile.getPosition();
		mView.showMessage(pos);
	};
	static auto getLengthFileHandler = [this]() {
		auto length = mFile.getLength();
		mView.showMessage(length);
	};
	static auto readIntFileHandler = [this]() {
		int number;
		mFile.read(reinterpret_cast<char*>(&number), sizeof(number));
		mView.showMessage(number);
	};
	static auto readStringFileHandler = [this]() {
		auto count = getInt(Messages::EnterCharactersCount, true);
		std::string str(count, ' ');
		mFile.read(str.data(), count);
		mView.showMessage(str);
	};
	static auto readDoubleFileHandler = [this]() {
		double d;
		mFile.read(reinterpret_cast<char*>(&d), sizeof(d));
		mView.showMessage(d);
	};
	static auto writeIntFileHandler = [this]() {
		auto input = getInt(Messages::InputInt, false);
		mFile.write(reinterpret_cast<char*>(&input), sizeof(input));
		mView.showMessage(Messages::WriteSuccess);
	};
	static auto writeStringFileHandler = [this]() {
		mView.showMessage(Messages::InputString);
		auto input = mView.getStringLine();
		mFile.write(input.data(), input.size());
		mView.showMessage(Messages::WriteSuccess);
	};
	static auto writeDoubleFileHandler = [this]() {
		auto input = getDouble(Messages::InputDouble);
		mFile.write(reinterpret_cast<char*>(&input), sizeof(input));
		mView.showMessage(Messages::WriteSuccess);
	};
	static auto createDataFileHandler = [this]() {
		mView.showMessage(Messages::EnterFilename);
		auto name = mView.getStringLine();
		mDataFile.open(name, File::Mode::Trunc);
		mView.showMessage(Messages::OpenSuccess);
	};
	static auto openDataFileHandler = [this]() {
		mView.showMessage(Messages::EnterFilename);
		auto name = mView.getStringLine();
		mDataFile.open(name, File::Mode::Open);
		mView.showMessage(Messages::OpenSuccess);
	};
	static auto closeDataFileHandler = [this]() {
		mDataFile.close();
		mView.showMessage(Messages::CloseSuccess);
	};
	static auto readDataFileHandler = [this]() {
		DataFile::Data data;
		auto idx = getInt(Messages::InputIndex, true);
		mDataFile.read(data, idx);
		mView.showMessage("a: ", data.a, ", b: ", data.b, ", c: ", data.c, ", name: ", data.name.data());
	};
	static auto writeDataFileHandler = [this]() {
		auto data = getData(Messages::InputDataStruct);
		auto idx = getInt(Messages::InputIndex, true);
		mDataFile.write(data, idx);
		mView.showMessage(Messages::WriteSuccess);
	};
	static auto appendDataFileHandler = [this]() {
		auto data = getData(Messages::InputDataStruct);
		mDataFile.append(data);
		mView.showMessage(Messages::AppendSuccess);
	};
	static auto getCountDataFileHandler = [this]() {
		auto length = mDataFile.getDataCount();
		mView.showMessage(length);
	};
	while (true) {
		try
		{
			auto actionCode = mView.runMenu();
			switch (actionCode) {
			case ActionCode::CreateFile:
				createFileHandler();
				break;
			case ActionCode::OpenFile:
				openFileHandler();
				break;
			case ActionCode::CloseFile:
				closeFileHandler();
				break;
			case ActionCode::SeekFile:
				seekFileHandler();
				break;
			case ActionCode::GetPositionFile:
				getPositionFileHandler();
				break;
			case ActionCode::GetLengthFile:
				getLengthFileHandler();
				break;
			case ActionCode::ReadIntFile:
				readIntFileHandler();
				break;
			case ActionCode::ReadStringFile:
				readStringFileHandler();
				break;
			case ActionCode::ReadDoubleFile:
				readDoubleFileHandler();
				break;
			case ActionCode::WriteIntFile:
				writeIntFileHandler();
				break;
			case ActionCode::WriteStringFile:
				writeStringFileHandler();
				break;
			case ActionCode::WriteDoubleFile:
				writeDoubleFileHandler();
				break;
			case ActionCode::CreateDataFile:
				createDataFileHandler();
				break;
			case ActionCode::OpenDataFile:
				openDataFileHandler();
				break;
			case ActionCode::CloseDataFile:
				closeDataFileHandler();
				break;
			case ActionCode::ReadDataFile:
				readDataFileHandler();
				break;
			case ActionCode::SetDataFile:
				writeDataFileHandler();
				break;
			case ActionCode::AppendDataFile:
				appendDataFileHandler();
				break;
			case ActionCode::GetCountDataFile:
				getCountDataFileHandler();
				break;
			case ActionCode::Exit:
				mView.showMessage(Messages::Exit);
				return;
			case ActionCode::UnsupportedKey:
			default:
				mView.showErrorMessage(ErrorMessages::UnsupportedMenuKey);
				break;
			}
		}
		catch (const Exception& ex)
		{
			mView.showErrorMessage(ErrorMessages::ErrorHappened, ex.what());
		}
	}
}

int Application::getInt(const std::string& message, bool positiveCheck) {
	mView.showMessage(message);
	auto inputStream = std::istringstream(mView.getStringLine());
	int input = 0;
	bool result = (inputStream >> input && inputStream.eof());
	if (inputStream.fail() || !result) {
		throw InputException(ErrorMessages::IncorrectIntInput);
	}
	if (positiveCheck && input < 0) {
		throw InputException(ErrorMessages::NotNegativeValue);
	}
	return input;
}

double Application::getDouble(const std::string& message) {
	mView.showMessage(message);
	auto inputStream = std::istringstream(mView.getStringLine());
	double input = 0;
	bool result = (inputStream >> input && inputStream.eof());
	if (inputStream.fail() || !result) {
		throw InputException(ErrorMessages::IncorrectDoubleInput);
	}
	return input;
}

DataFile::Data Application::getData(const std::string& message) {
	mView.showMessage(message);
	DataFile::Data data;
	std::istringstream is(mView.getStringLine());
	std::string name;
	bool result = (is >> name >> data.a >> data.b >> data.c) && (is.eof());
	if (is.fail() || !result) {
		throw InputException(ErrorMessages::IncorrectDataInput);
	}
	if (name.length() > DataFile::Data::NameSize) {
		mView.showMessage(Messages::TooLongName);
		name.resize(DataFile::Data::NameSize);
	}
	std::strcpy(data.name.data(), name.c_str());
	data.name.back() = '\0';
	return data;
}
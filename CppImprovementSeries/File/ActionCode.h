#pragma once

enum class ActionCode {
	Exit,
	None,
	OpenFile,
	CloseFile,
	SeekFile,
	GetPositionFile,
	GetLengthFile,
	ReadIntFile,
	ReadStringFile,
	ReadDoubleFile,
	WriteIntFile,
	WriteStringFile,
	WriteDoubleFile,
	OpenDataFile,
	CloseDataFile,
	ReadDataFile,
	WriteDataFile,
	GetCountDataFile
};
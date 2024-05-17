#pragma once

enum class ActionCode {
	Exit,
	UnsupportedKey,
	CreateFile,
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
	CreateDataFile,
	OpenDataFile,
	CloseDataFile,
	ReadDataFile,
	SetDataFile,
	AppendDataFile,
	GetCountDataFile
};
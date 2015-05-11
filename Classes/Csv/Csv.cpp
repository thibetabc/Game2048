#include "Csv/Csv.h"
#include <stdio.h>

Csv::Csv()
{

}

Csv::~Csv()
{

}

void Csv::Test()
{
	Csv csv;
	csv.Load("Split.csv");
	vector<vector<string>> &csvData = csv.GetGridData();
}

void Csv::Load(const string &strFileName)
{

	string data;
	ReadAll(strFileName, data);
	Parse(data);

}
void Csv::ReadAll(const string &strFileName, string &data)
{
	if (strFileName.empty())
	{
		return;
	}
	FILE *file = fopen(strFileName.c_str(), "rb");
	if (file == nullptr)
	{
		return;
	}
	fseek(file, 0, SEEK_END);
	
	long len = ftell(file);
	char *pBuffer = new char[len + 1];
	
	fseek(file, 0, SEEK_SET);
	fread(pBuffer, 1, len, file);
	fclose(file);

	pBuffer[len] = 0;
	data.assign(pBuffer, len);

	delete[]pBuffer;

}

void Csv::Parse(const string &data)
{
	// 清除之前的数据   
	m_gridData.clear();
	// 分出行，分出字段
	vector<string> ret;
	Split(data, "\r\n", ret);
	for (size_t i = 0; i < ret.size(); ++i)
	{
		vector<string> fields;
		Split(ret[i], ",", fields);
		m_gridData.push_back(fields);
	}
}

void Csv::Split(const string &str, const string &seperator, vector<string> &ret)
{
	ret.clear();
	size_t nStartPosFound = str.find(seperator, 0);
	size_t nFieldStart = 0;
	for (; nStartPosFound != -1; nStartPosFound = str.find(seperator, nStartPosFound))
	{
		string strSub = str.substr(nFieldStart, nStartPosFound - nFieldStart);
		nStartPosFound = nStartPosFound + seperator.size();
		nFieldStart = nStartPosFound;
		ret.push_back(strSub);
	}

	// 加入最后一个字段
	if (nFieldStart < str.size())
	{
		string strSub = str.substr(nFieldStart, str.size() - nFieldStart);
		ret.push_back(strSub);
	}
}


#pragma once

#include <vector>
#include <string>

using namespace std;
//http://blog.csdn.net/stevenkylelee/article/details/38309147
class Csv
{
public:
	Csv();
	~Csv();
public:
	static void Test();
public:
	// 载入一个CSV文件 
	void Load(const string &strFileName);
	// 从字符串从解析
	void Parse(const string &strText);
public:
	/*
	分割字符串
	str 要分隔的字符串
	seperator 分隔符
	Ret 分割后的结果
	*/
	static void Split(const string &str, const string &seperate, vector<string> &ret);
	/*
	读取整个文件的数据
	*/
	static void ReadAll(const string &strFileName, string &data);
	vector<vector<string>> GetGridData(){ return m_gridData; };
public:
	//vector<vector<string>>

private:
	vector<vector<string>> m_gridData;
};
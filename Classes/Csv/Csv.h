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
	// ����һ��CSV�ļ� 
	void Load(const string &strFileName);
	// ���ַ����ӽ���
	void Parse(const string &strText);
public:
	/*
	�ָ��ַ���
	str Ҫ�ָ����ַ���
	seperator �ָ���
	Ret �ָ��Ľ��
	*/
	static void Split(const string &str, const string &seperate, vector<string> &ret);
	/*
	��ȡ�����ļ�������
	*/
	static void ReadAll(const string &strFileName, string &data);
	vector<vector<string>> GetGridData(){ return m_gridData; };
public:
	//vector<vector<string>>

private:
	vector<vector<string>> m_gridData;
};
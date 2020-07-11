
/*
* fuzzy_search.h
*
*  Created on: 2018年5月23日
*      Author: miloofzhang
*
*  字符串模糊查询 支持所有utf-8字符串
*/


#pragma once

#include <map>
#include <string>
#include <list>
#include <set>
#include <vector>
#include <iostream>

struct ResultData
{
	std::string str;
	unsigned int userData;
};

class IFuzzySearch
{
public:
	//添加一个字符串
	virtual void AddString(const std::string str, unsigned int userData = 0) = 0;
	//删除一个字符串
	virtual void DeleteString(const std::string str) = 0;
	//查询是否包含字符串
	virtual bool HasString(const std::string str) = 0;
	//获取字符串的用户数据
	virtual unsigned int GetStringUserData(const std::string str) = 0;
	//设置字符串的用户数据
	virtual void SetStringUserData(const std::string str, unsigned int userData) = 0;
	//模糊查询一个字符串，results为匹配到的字符串， limit限制返回的字符串数量
	virtual void SearchStringLike(const std::string str, std::list<ResultData>& results, int limit = 100) = 0;
};

struct TrieNode;
class CFuzzyTrie : public IFuzzySearch
{
public:
	void AddString(const std::string str, unsigned int userData = 0);
	void DeleteString(const std::string str);
	bool HasString(const std::string str);
	unsigned int GetStringUserData(const std::string str);
	void SetStringUserData(const std::string str, unsigned int userData);
	void SearchStringLike(const std::string str, std::list<ResultData>& results, int limit = 100);
public:
	CFuzzyTrie();
	~CFuzzyTrie();
	//打印树结构，测试用
	void PrintTrie();
	//统计树节点数量，测试用
	void CountNode();
	void CountNode(TrieNode* pNode, unsigned int & num, unsigned int & strNum);
private:
	//获取字符串下一个有效UTF-8字符的字节数
	int GetNextCharacterBytes(const char* pStr);
	//把一个UTF-8字符转换成整数
	unsigned int GetCharacterInt(const char* pCharacter, int byteLen);
	//往树中插入一个字符串
	void AddToResourceTrie(const char* pStr, int len, unsigned int userData = 0);
	//索引key为4字节，所以对节点建立索引的时候，会生成所有小于等于4字节的索引组合
	//比如： 字符串abcd， 添加d节点的时候，会生成 abcd,bcd,cd,d 四个索引
	void SetIndex(TrieNode* pNode, int level);
	void DelIndex(TrieNode* pNode, int level);
	//获取pStartNode节点开始的str字符串的结束节点
	TrieNode* GetSubstrEndNode(TrieNode* pStartNode, const std::string str, int* pCharacterCnt = NULL);
	//获取pNode开始的str字符串模糊匹配出来的所有字符串
	void SearchStringLikeByNode(TrieNode* pNode, const std::string str, std::list<ResultData>& results, int& limit);
	//获取pNode开始的str字符串的前缀字符串（包含str）
	void GetPrefix(TrieNode* pNode, std::string& str);
	//为前缀字符串pre添加所有可能的后缀，并添加到strList
	void AppendSuffix(std::string& pre, TrieNode* pNode, std::list<ResultData>& strList, int& limit);
	void AppendSuffix(std::string& pre, TrieNode* pNode, std::list<ResultData>& strList, std::string str, int& limit);
private:
	typedef std::vector<TrieNode*> TIndexNodes;
	typedef std::map<unsigned int, TIndexNodes> TIndex;
	std::map<unsigned int, TIndex> m_indexByLevel;
	std::set<TrieNode*> m_resultWordEnds;
	TrieNode* m_pTrieRoot;
};

//CharacterTrans:
//用来辅助生成节点key的union，同时整合进来一个字符串结束标志
//节点key说明：
//	  utf-8所有字符，最多会有可能会有个1-4个字节
//	  为了加快索引速度，所有索引子节点的key都转换成了字符对应的int整型
//字符串end标志说明：
//    用了一个utf-8字符的特性，多字节字符从第二个字节开始，每个字节都是10开头
//    所以用第二个字节的由高到低第二位来做结束标志
union CharacterTrans
{
	char chars[4];
	unsigned int chars_int;
	//设置字符
	void SetCharacter(const char* pCharacter, int byteLen);
	//返回字符对应的int表示
	unsigned int GetCharacterInt();
	//返回字符
	std::string GetCharacter();
	//获取字符的有效字节数
	int GetCharacterBytes();
	//往字符的空闲位置添加一个特殊标记（字符串结束标记）
	void SetEndMark();
	void ClearEndMark();
	bool IsEnd();
};

//NodeData
//userData存储用户自定义的一个int整型
struct NodeData
{
	CharacterTrans character;
	unsigned int userData;

	NodeData();
	void SetEndMark();
	void ClearEndMark();
	bool IsEnd();
	void SetCharacter(const char* pCharacter, int byteLen);
	unsigned int GetCharacterInt();
	std::string GetCharacter();
	int GetCharacterBytes();
	void SetUserData(unsigned int d);
	unsigned int GetUserData();
};

//为了支持模糊查询，加入了一个指向父节点的指针
struct TrieNode
{
	std::map<unsigned int, TrieNode> next;
	TrieNode* father;
	NodeData data;
	TrieNode();
	void SetUserData(unsigned int d);
	unsigned int GetUserData();
	bool IsEnd();
	void PrintNode();
};
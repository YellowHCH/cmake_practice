#include "fuzzy_search.h"

void CFuzzyTrie::AddString(const std::string str, unsigned int userData/* = 0*/)
{
	AddToResourceTrie(str.c_str(), str.length(), userData);
}

void CFuzzyTrie::DeleteString(const std::string str)
{
	//要删除的字符串如果存在的话，肯定是从树的0层开始的
	int characterBytes = GetNextCharacterBytes(str.c_str());
	unsigned int key = GetCharacterInt(str.c_str(), characterBytes);
	TIndex::iterator iter = m_indexByLevel[0].find(key);
	if (iter == m_indexByLevel[0].end())
	{
		return;
	}
	for (TIndexNodes::iterator it = iter->second.begin(); it != iter->second.end(); ++it)
	{
		int strCharacterCnt = 0;
		//找出str的结束节点
		TrieNode* pEndNode = GetSubstrEndNode(*it, str.c_str(), &strCharacterCnt);
		if (NULL == pEndNode)
		{
			continue;
		}
		if (!pEndNode->data.IsEnd())
		{
			continue;
		}
		pEndNode->data.ClearEndMark();
		while (pEndNode != m_pTrieRoot)
		{
			//反向遍历父节点，如果没有子节点，而且不是字符串结束节点的话，就删掉
			if (!pEndNode->next.empty() || pEndNode->IsEnd())
			{
				break;
			}
			DelIndex(pEndNode, --strCharacterCnt);
			unsigned int chaIntEnd = pEndNode->data.GetCharacterInt();
			pEndNode = pEndNode->father;
			pEndNode->next.erase(chaIntEnd);
		}
		break;
	}
}

bool CFuzzyTrie::HasString(const std::string str)
{
	int characterBytes = GetNextCharacterBytes(str.c_str());
	unsigned int key = GetCharacterInt(str.c_str(), characterBytes);
	TIndex::iterator iter = m_indexByLevel[0].find(key);
	if (iter == m_indexByLevel[0].end())
	{
		return false;
	}
	for (TIndexNodes::iterator it = iter->second.begin(); it != iter->second.end(); ++it)
	{
		TrieNode* pEndNode = GetSubstrEndNode(*it, str.c_str());
		if (NULL != pEndNode)
		{
			if (pEndNode->data.IsEnd())
			{
				return true;
			}
		}
	}
	return false;
}

unsigned int CFuzzyTrie::GetStringUserData(const std::string str)
{
	int characterBytes = GetNextCharacterBytes(str.c_str());
	unsigned int key = GetCharacterInt(str.c_str(), characterBytes);
	TIndex::iterator iter = m_indexByLevel[0].find(key);
	if (iter == m_indexByLevel[0].end())
	{
		return 0;
	}
	for (TIndexNodes::iterator it = iter->second.begin(); it != iter->second.end(); ++it)
	{
		TrieNode* pEndNode = GetSubstrEndNode(*it, str.c_str());
		if (NULL != pEndNode)
		{
			if (pEndNode->data.IsEnd())
			{
				return pEndNode->GetUserData();
			}
		}
	}
	return 0;
}

void CFuzzyTrie::SetStringUserData(const std::string str, unsigned int userData)
{
	int characterBytes = GetNextCharacterBytes(str.c_str());
	unsigned int key = GetCharacterInt(str.c_str(), characterBytes);
	TIndex::iterator iter = m_indexByLevel[0].find(key);
	if (iter == m_indexByLevel[0].end())
	{
		return;
	}
	for (TIndexNodes::iterator it = iter->second.begin(); it != iter->second.end(); ++it)
	{
		TrieNode* pEndNode = GetSubstrEndNode(*it, str.c_str());
		if (NULL != pEndNode)
		{
			if (pEndNode->data.IsEnd())
			{
				pEndNode->SetUserData(userData);
				return;
			}
		}
	}
}

void CFuzzyTrie::SearchStringLike(const std::string str, std::list<ResultData>& results, int limit /*= 100*/)
{
	int maxIndexStrBytes = 0;
	int offect = 0;
	while (((int)str.length() > offect) && (4 > offect))
	{
		offect += GetNextCharacterBytes(str.c_str() + offect);
		maxIndexStrBytes = (4 < offect) ? maxIndexStrBytes : offect;
	}
	unsigned int key = GetCharacterInt(str.c_str(), maxIndexStrBytes);

	int limitRest = limit;
	//从第0层节点的索引开始遍历，优先找出完全匹配的字符串
	for (std::map<unsigned int, TIndex>::iterator iterLevel = m_indexByLevel.begin(); (iterLevel != m_indexByLevel.end()) && (0 < limitRest); ++iterLevel)
	{
		TIndex::iterator iterKey = iterLevel->second.find(key);
		if (iterKey == iterLevel->second.end())
		{
			continue;
		}
		TIndexNodes &nodeList = iterKey->second;
		for (TIndexNodes::iterator iter = nodeList.begin(); (iter != nodeList.end()) && (0 < limitRest); ++iter)
		{
			SearchStringLikeByNode(*iter, str, results, limitRest);
		}
	}
    
    m_resultWordEnds.clear();
}

CFuzzyTrie::CFuzzyTrie()
{
	m_pTrieRoot = new TrieNode;
}

CFuzzyTrie::~CFuzzyTrie()
{
	delete m_pTrieRoot;
}

void CFuzzyTrie::PrintTrie()
{
	m_pTrieRoot->PrintNode();
}

void CFuzzyTrie::CountNode(TrieNode* pNode, unsigned int & num, unsigned int & strNum)
{
	++num;
	if (pNode->data.IsEnd())
	{
		++strNum;
	}
	for (std::map<unsigned int, TrieNode>::iterator iter = pNode->next.begin(); iter != pNode->next.end(); ++iter)
	{
		CountNode(&(iter->second), num, strNum);
	}
}

void CFuzzyTrie::CountNode()
{
	unsigned int num = 0;
	unsigned int strNum = 0;
	CountNode(m_pTrieRoot, num, strNum);
	std::cout << "node count : " << num << std::endl;
	std::cout << "str count : " << strNum << std::endl;
}

int CFuzzyTrie::GetNextCharacterBytes(const char* pStr)
{
	int characterBytes = 0;
	char detector = 0x80;
	do
	{
		++characterBytes;
		detector = detector >> 1;
	} while (((*pStr & detector) == detector) && (detector != (char)0xFF));
	if (characterBytes > UTF8_MAX_BYTES)
	{
		//不是一个正常的UTF-8头，强行置一
		characterBytes = 1;
	}
	return characterBytes;
}

unsigned int CFuzzyTrie::GetCharacterInt(const char* pCharacter, int byteLen)
{
	CharacterTrans chaTemp;
	chaTemp.SetCharacter(pCharacter, byteLen);
	return chaTemp.GetCharacterInt();
}

void CFuzzyTrie::AddToResourceTrie(const char* pStr, int len, unsigned int userData/* = 0*/)
{
	TrieNode* pFatherNode = m_pTrieRoot;
	TrieNode* pSonNode = m_pTrieRoot;

	int offect = 0;
	int level = 0;

	while (offect < len)
	{
		int characterBytes = GetNextCharacterBytes(pStr + offect);
		unsigned int key = GetCharacterInt(pStr + offect, characterBytes);
		std::map<unsigned int, TrieNode>::iterator iter = pFatherNode->next.find(key);
		if (iter == pFatherNode->next.end())
		{
			pSonNode = &(pFatherNode->next[key]);
			pSonNode->data.SetCharacter(pStr + offect, characterBytes);
			pSonNode->father = pFatherNode;
			SetIndex(pSonNode, level);
		}
		else
		{
			pSonNode = &(iter->second);
		}
		pFatherNode = pSonNode;
		++level;
		offect += characterBytes;
	}
	pSonNode->data.SetEndMark();
	pSonNode->SetUserData(userData);
}

void CFuzzyTrie::SetIndex(TrieNode* pNode, int level)
{
	TrieNode* pCurNode = pNode;
	int curLevel = level;
	std::string str;
	unsigned int bytesNum = 0;
	while (4 > bytesNum && 0 <= curLevel)
	{
		if (pCurNode == m_pTrieRoot)
		{
			return;
		}
		bytesNum += pCurNode->data.GetCharacterBytes();
		if (4 < bytesNum)
		{
			return;
		}
		str = pCurNode->data.GetCharacter() + str;
		unsigned int keyInt = GetCharacterInt(str.c_str(), bytesNum);
		m_indexByLevel[curLevel--][keyInt].push_back(pCurNode);
		pCurNode = pCurNode->father;
	}
}

void CFuzzyTrie::DelIndex(TrieNode* pNode, int level)
{
	TrieNode* pCurNode = pNode;
	int curLevel = level;
	std::string str;
	unsigned int bytesNum = 0;
	while (4 > bytesNum && 0 <= curLevel)
	{
		if (pCurNode == m_pTrieRoot)
		{
			return;
		}
		bytesNum += pCurNode->data.GetCharacterBytes();
		if (4 < bytesNum)
		{
			return;
		}
		str = pCurNode->data.GetCharacter() + str;
		unsigned int keyInt = GetCharacterInt(str.c_str(), bytesNum);
		
        TIndex& refIndex = m_indexByLevel[curLevel];
		TIndexNodes& refIndexNodes = refIndex[keyInt];

		for (TIndexNodes::iterator iter = refIndexNodes.begin(); iter != refIndexNodes.end(); ++iter)
		{
			if (*iter == pCurNode)
			{
				refIndexNodes.erase(iter);
				break;   //这里直接break掉，不必担心crash问题
			}
		}

		if (refIndexNodes.empty())
		{
			refIndex.erase(keyInt);
		}
        
		curLevel--;
		pCurNode = pCurNode->father;
	}
}

TrieNode* CFuzzyTrie::GetSubstrEndNode(TrieNode* pStartNode, const std::string str, int* pCharacterCnt /*= NULL*/)
{
	TrieNode* pEnd = pStartNode;
	int characterBytes = GetNextCharacterBytes(str.c_str());
	unsigned int offect = characterBytes, characterCnt = 1;
	bool bFound = true;
	while (offect < str.length())
	{
		characterBytes = GetNextCharacterBytes(str.c_str() + offect);
		unsigned int key = GetCharacterInt(str.c_str() + offect, characterBytes);
		offect += characterBytes;
		++characterCnt;
		std::map<unsigned int, TrieNode>::iterator iterNode = pEnd->next.find(key);
		if (iterNode == pEnd->next.end())
		{
			bFound = false;
			break;
		}
		pEnd = &(iterNode->second);
	}
	if (!bFound)
	{
		pEnd = NULL;
	}
	if (NULL != pCharacterCnt)
	{
		*pCharacterCnt = characterCnt;
	}

	return pEnd;
}

void CFuzzyTrie::SearchStringLikeByNode(TrieNode* pNode, const std::string str, std::list<ResultData>& results, int& limit)
{
	TrieNode* pStrEndNode = GetSubstrEndNode(pNode, str);
	if (NULL == pStrEndNode)
	{
		return;
	}
	std::string strPre;
	GetPrefix(pStrEndNode, strPre);
	AppendSuffix(strPre, pStrEndNode, results, limit);
}

void CFuzzyTrie::GetPrefix(TrieNode* pNode, std::string& str)
{
	if (NULL == pNode->father)
	{
		return;
	}
	GetPrefix(pNode->father, str);
	str += pNode->data.GetCharacter();
}

void CFuzzyTrie::AppendSuffix(std::string& pre, TrieNode* pNode, std::list<ResultData>& strList, std::string str, int& limit)
{
	if (pNode->data.IsEnd() && (m_resultWordEnds.find(pNode) == m_resultWordEnds.end()))
	{
		ResultData tmpData;
		tmpData.str = pre + str;
		tmpData.userData = pNode->GetUserData();
		strList.push_back(tmpData);
		m_resultWordEnds.insert(pNode);
		--limit;
	}
	for (std::map<unsigned int, TrieNode>::iterator iter = pNode->next.begin(); iter != pNode->next.end(); ++iter)
	{
		if (0 >= limit)
		{
			break;
		}
		AppendSuffix(pre, &(iter->second), strList, str + iter->second.data.GetCharacter(), limit);
	}
}

void CFuzzyTrie::AppendSuffix(std::string& pre, TrieNode* pNode, std::list<ResultData>& strList, int& limit)
{
	AppendSuffix(pre, pNode, strList, "", limit);
}

void CharacterTrans::SetCharacter(const char* pCharacter, int byteLen)
{
	if (4 < byteLen)
	{
		return;
	}
	chars_int = 0;
	for (int i = 0; i < byteLen; ++i)
	{
		chars[i] = *(pCharacter + i);
	}
}

unsigned int CharacterTrans::GetCharacterInt()
{
	bool isEnd = IsEnd();
	if (isEnd)
	{
		ClearEndMark();
	}
	unsigned int tmp = chars_int;
	if (isEnd)
	{
		SetEndMark();
	}
	return tmp;
}

std::string CharacterTrans::GetCharacter()
{
	bool isEnd = IsEnd();
	if (isEnd)
	{
		ClearEndMark();
	}
	char tmp[5] = { 0 };
	for (int i = 0; i < 4; ++i)
	{
		tmp[i] = chars[i];
	}
	if (isEnd)
	{
		SetEndMark();
	}
	return tmp;
}

int CharacterTrans::GetCharacterBytes()
{
	int characterBytes = 0;
	char detector = 0x80;
	do
	{
		++characterBytes;
		detector = detector >> 1;
	} while (((chars[0] & detector) == detector) && (detector != (char)0xFF));
	if (characterBytes > UTF8_MAX_BYTES)
	{
		//不是一个正常的UTF-8头，强行置一
		characterBytes = 1;
	}
	return characterBytes;
}

void CharacterTrans::SetEndMark()
{
	chars_int |= 0x400000;
}

void CharacterTrans::ClearEndMark()
{
	chars_int &= 0xFFBFFFFF;
}

bool CharacterTrans::IsEnd()
{
	return (chars_int & 0x400000) == 0x400000;
}

NodeData::NodeData() : userData(0)
{
	character.SetCharacter("", 0);
}

void NodeData::SetEndMark()
{
	character.SetEndMark();
}

void NodeData::ClearEndMark()
{
	character.ClearEndMark();
}

bool NodeData::IsEnd()
{
	return character.IsEnd();
}

void NodeData::SetCharacter(const char* pCharacter, int byteLen)
{
	character.SetCharacter(pCharacter, byteLen);
}

unsigned int NodeData::GetCharacterInt()
{
	return character.GetCharacterInt();
}

std::string NodeData::GetCharacter()
{
	return character.GetCharacter();
}

int NodeData::GetCharacterBytes()
{
	return character.GetCharacterBytes();
}

void NodeData::SetUserData(unsigned int d)
{
	userData = d;
}

unsigned int NodeData::GetUserData()
{
	return userData;
}

TrieNode::TrieNode() : father(NULL)
{

}

void TrieNode::SetUserData(unsigned int d)
{
	data.SetUserData(d);
}

unsigned int TrieNode::GetUserData()
{
	return data.GetUserData();
}


bool TrieNode::IsEnd()
{
	return data.IsEnd();
}

void TrieNode::PrintNode()
{
	if (NULL != father)
	{
		std::cout << " " << data.GetCharacter();
	}
	if (data.IsEnd())
	{
		std::cout << " | ";
	}
	if (next.empty())
	{
		std::cout << std::endl;
	}
	for (std::map<unsigned int, TrieNode>::iterator iter = next.begin(); iter != next.end(); ++iter)
	{
		iter->second.PrintNode();
	}
}

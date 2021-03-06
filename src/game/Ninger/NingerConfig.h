#ifndef NINGER_CONFIG_H
#define NINGER_CONFIG_H

#include "Common.h"
#include <ace/Recursive_Thread_Mutex.h>
#include <ace/Singleton.h>
#include "Platform/Define.h"
#include "ace/Configuration_Import_Export.h"

class ACE_Configuration_Heap;

class NingerConfig
{
	friend class ACE_Singleton<NingerConfig, ACE_Recursive_Thread_Mutex>;
public:

	NingerConfig();
	~NingerConfig();

	bool SetSource(char const* file);
	bool Reload();

	std::string GetStringDefault(char const* name, char const* def);
	bool GetBoolDefault(char const* name, bool const def = false);
	int32 GetIntDefault(char const* name, int32 const def);
	float GetFloatDefault(char const* name, float const def);

	std::string GetFilename() const { return mFilename; }
	bool GetValueHelper(char const* name, ACE_TString& result);

private:

	std::string mFilename;
	ACE_Configuration_Heap* mConf;

	typedef ACE_Thread_Mutex LockType;
	typedef ACE_Guard<LockType> GuardType;

	std::string _filename;
	LockType m_configLock;

public:

	bool StartNingerSystem();
	uint32 Enable;
	std::string AccountNamePrefix;
	uint32 DPSDelay;
	uint32 OnlineCheckDelay;
	uint32 OfflineCheckDelay;
	uint32 NingerCountEachLevel;

	std::vector<std::string> SplitString(std::string srcStr, std::string delimStr, bool repeatedCharIgnored);
	std::string TrimString(std::string srcStr);
};

#define sNingerConfig (*ACE_Singleton<NingerConfig, ACE_Recursive_Thread_Mutex>::instance())

#endif

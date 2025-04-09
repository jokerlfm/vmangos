#include "MingConfig.h"
#include "Policies/SingletonImp.h"

#ifndef MING_CONFIG_FILE_NAME
# define MING_CONFIG_FILE_NAME  "ming.conf"
#endif

INSTANTIATE_SINGLETON_1(MingConfig);

// Defined here as it must not be exposed to end-users.
bool MingConfig::GetValueHelper(char const* name, ACE_TString& result)
{
    GuardType guard(m_configLock);

    if (!mConf)
        return false;

    ACE_TString section_name;
    ACE_Configuration_Section_Key section_key;
    ACE_Configuration_Section_Key const& root_key = mConf->root_section();

    int i = 0;
    while (mConf->enumerate_sections(root_key, i, section_name) == 0)
    {
        mConf->open_section(root_key, section_name.c_str(), 0, section_key);
        if (mConf->get_string_value(section_key, name, result) == 0)
            return true;
        ++i;
    }

    return false;
}

MingConfig::MingConfig()
    : mConf(nullptr)
{
}

MingConfig::~MingConfig()
{
    delete mConf;
}

bool MingConfig::SetSource(char const* file)
{
    mFilename = file;

    return Reload();
}

bool MingConfig::Reload()
{
    delete mConf;
    mConf = new ACE_Configuration_Heap;

    if (mConf->open() != -1)
    {
        ACE_Ini_ImpExp config_importer(*mConf);
        if (config_importer.import_config(mFilename.c_str()) != -1)
            return true;
    }

    delete mConf;
    mConf = nullptr;
    return false;
}

std::string MingConfig::GetStringDefault(char const* name, char const* def)
{
    ACE_TString val;
    return GetValueHelper(name, val) ? val.c_str() : def;
}

bool MingConfig::GetBoolDefault(char const* name, bool def)
{
    ACE_TString val;
    if (!GetValueHelper(name, val))
        return def;

    char const* str = val.c_str();
    return strcmp(str, "true") == 0 || strcmp(str, "TRUE") == 0 ||
        strcmp(str, "yes") == 0 || strcmp(str, "YES") == 0 ||
        strcmp(str, "1") == 0;
}


int32 MingConfig::GetIntDefault(char const* name, int32 def)
{
    ACE_TString val;
    return GetValueHelper(name, val) ? atoi(val.c_str()) : def;
}


float MingConfig::GetFloatDefault(char const* name, float def)
{
    ACE_TString val;
    return GetValueHelper(name, val) ? (float)atof(val.c_str()) : def;
}

bool MingConfig::StartMingSystem()
{
    SetSource(MING_CONFIG_FILE_NAME);
    Reload();

    Enable = GetIntDefault("Enable", 0);
    Reset = GetIntDefault("Reset", 0);
    SellingItemsMax = GetIntDefault("SellingItemsMax", 100);
    BuyingItemsMax = GetIntDefault("BuyingItemsMax", 100);
    BuyerId = GetIntDefault("BuyerId", 0);
    BuyerViewRate = GetFloatDefault("BuyerViewRate", 0.1f);
    BuyerBuyRate = GetFloatDefault("BuyerBuyRate", 1.0f);
    ManagerCheckDelay = GetIntDefault("ManagerCheckDelay", 60000);
    VenderReplaceDelay_Min = GetIntDefault("VenderReplaceDelay_Min", 3600000);
    VenderReplaceDelay_Max = GetIntDefault("VenderReplaceDelay_Max", 7200000);

    if (Enable == 0)
    {
        sLog.Out(LOG_BASIC, LOG_LVL_BASIC, "Ming system is disabled.");
        return false;
    }
    sLog.Out(LOG_BASIC, LOG_LVL_BASIC, "Ming system started.");
    return true;
}

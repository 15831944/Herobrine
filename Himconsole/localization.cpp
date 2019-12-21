// Copyright 2019 SMS
// License(Apache-2.0)
// ���ػ�

#include "localization.h"



#ifdef LANG_EN
const char* LOC_WARN_DEBUG             = "This version is built in development for debugging only";
const char* LOC_ERROR_UNKNOWN_COMMAND  = "Unknown command";
const char* LOC_ERROR_COMMAND_TOO_LONG = "Command too long";
#endif

#ifdef LANG_ZH_CN
const char* LOC_WARN_DEBUG             = "�ð汾�ڿ����й���, ����������";
const char* LOC_ERROR_UNKNOWN_COMMAND  = "δ֪����";
const char* LOC_ERROR_COMMAND_TOO_LONG = "�������";
const char* LOC_ERROR_INVALID_ARGUMENT = "��Ч����";
#endif

#ifdef LANG_ZH_TW
const char* LOC_WARN_DEBUG             = "ԓ�汾��_�l�И���, �H���{ԇ��";
const char* LOC_ERROR_UNKNOWN_COMMAND  = "δ֪����";
const char* LOC_ERROR_COMMAND_TOO_LONG = "�����^�L";
#endif



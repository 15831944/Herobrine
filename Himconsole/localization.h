// Copyright 2019 SMS
// License(Apache-2.0)
// ���ػ�

#ifndef LOCALIZATION_H_
#define LOCALIZATION_H_



/*
 ����(Language)
 LANG_ZH_CH ���ļ���
 LANG_ZH_TW ���ķ��w
 LANG_EN    English
 */
#define LANG_ZH_CN

#ifdef LANG_EN
extern const char* LOC_WARN_DEBUG;
extern const char* LOC_ERROR_UNKNOWN_COMMAND;
extern const char* LOC_ERROR_COMMAND_TOO_LONG;
#endif

#ifdef LANG_ZH_CN
extern const char* LOC_WARN_DEBUG;
extern const char* LOC_ERROR_UNKNOWN_COMMAND;
extern const char* LOC_ERROR_COMMAND_TOO_LONG;
extern const char* LOC_ERROR_INVALID_ARGUMENT;
#endif

#ifdef LANG_ZH_TW
extern const char* LOC_WARN_DEBUG;
extern const char* LOC_ERROR_UNKNOWN_COMMAND;
extern const char* LOC_ERROR_COMMAND_TOO_LONG;
#endif



#endif // LOCALIZATION_H_

// Copyright 2019 SMS
// License(Apache-2.0)
// 本地化

#ifndef LOCALIZATION_H_
#define LOCALIZATION_H_

#include "include.h"



/*
 语言(Language)
 LANG_ZH_CN 中文简体
 LANG_ZH_TW 中文繁體
 LANG_EN    English
 */
#define LANG_ZH_CN

class Localization
{
public:
  const std::string& operator[](const std::string&);

private:
	map<std::string, std::string> dir;
};

extern Localization local;



#endif // LOCALIZATION_H_

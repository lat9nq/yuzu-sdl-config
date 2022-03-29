#pragma once
#include <common/settings.h>

class BasicIni;

template <typename T>
void LoadSetting(const BasicIni& ini, const std::string& section,
                 Settings::BasicSetting<T>& setting);
template <typename T>
void LoadEnumSetting(const BasicIni& ini, const std::string& section,
                     Settings::BasicSetting<T>& setting);

void LoadConfig(const BasicIni& ini, Settings::Values& settings);

template <typename T>
void ApplySetting(BasicIni& ini, const std::string& section,
                  const Settings::BasicSetting<T>& setting);
template <typename T>
void ApplyEnumSetting(BasicIni& ini, const std::string& section,
                      const Settings::BasicSetting<T>& setting);
void ApplySettings(BasicIni& ini, const Settings::Values& settings);

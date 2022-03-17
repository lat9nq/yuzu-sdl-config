#pragma once
#include <common/settings.h>

class BasicIni;

template <typename T>
void LoadSetting(const BasicIni& ini, const std::string& section,
                 Settings::BasicSetting<T>& setting);

void LoadConfig(const BasicIni& ini, Settings::Values& settings);
void ApplySettings(BasicIni& ini, const Settings::Values& settings);

#pragma once

namespace Settings {
struct Values;
}

class BasicIni;

void LoadConfig(BasicIni& ini, Settings::Values& settings);
void ApplySettings(BasicIni& ini, Settings::Values& settings);

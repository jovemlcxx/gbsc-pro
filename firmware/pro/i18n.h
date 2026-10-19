// ====================================================================================
// i18n.h
// UI language support (OLED, TV OSD, Web UI)
//
// All UI strings in the code base are written in English (en-US). tr() looks the
// English text up in a PROGMEM table and returns the pt-BR text when that language is
// active, or the original pointer otherwise. Unknown strings are returned unchanged,
// so untranslated text always falls back to English.
//
// Add a string:  append X("English", "Portugues") to I18N_TABLE in i18n.cpp.
// Constraint:    OSD/OLED fonts are ASCII only -> no accents in pt-BR text.
// ====================================================================================

#pragma once

#include <Arduino.h>

enum UiLang : uint8_t {
    LANG_EN = 0,   // en-US
    LANG_PT = 1,   // pt-BR
    LANG_COUNT
};

extern uint8_t uiLang;

// Translate an English UI string. Result is valid until 4 more tr() calls are made.
const char *tr(const char *en);

// Short code of the active language ("EN-US" / "PT-BR")
const char *i18nLangName(uint8_t lang);

// Persistence (/lang.txt on LittleFS, independent from preferencesv2.txt layout)
void i18nLoad();
void i18nSave();

// Cycle to the next language, save it and return the new value
uint8_t i18nNext();

// Bitmap menu text (OLEDMenuTranslations): returns the pt-BR bitmap matching an English one.
// If no translation is active/available, returns bits and leaves w/h untouched.
const uint8_t *i18nBitmap(const uint8_t *bits, uint16_t &w, uint16_t &h);

// ====================================================================================
// osd-main.cpp
// TV OSD Handlers for Main Menu and Cursor
// ====================================================================================

#include "../osd-core.h"

// ====================================================================================
// OSD Initialization
// ====================================================================================

// Fill background once when menu opens (called before any menu handler)
void handle_OSD_Init(void)
{
    OSD_fillBackground();
}

// ====================================================================================
// Main Menu Handlers
// ====================================================================================

void handle_MainMenu_Page1(void)
{
    // AV/SV Input Settings disabled when not SV/AV input
    bool isSvAvInput = (uopt->activeInputType == InputTypeSV) || (uopt->activeInputType == InputTypeAV);
    OSD_setMenuLineColors(selectedMenuLine);
    OSD_writePageIcons(false, '1', true);
    OSD_writeStringAtRow(1, 1, "Input source");
    OSD_writeStringAtRow(2, 1, "AV/SV settings", isSvAvInput ? OSD_COLOR_AUTO : OSD_TEXT_DISABLED);
    OSD_writeStringAtRow(3, 1, "Output resolution");
}

void handle_MainMenu_Page2(void)
{
    OSD_setMenuLineColors(selectedMenuLine);
    OSD_writePageIcons(true, '2', true);
    OSD_writeStringAtRow(1, 1, "Screen settings");
    OSD_writeStringAtRow(2, 1, "Picture settings");
    OSD_writeStringAtRow(3, 1, "System settings");
}

void handle_MainMenu_Page3(void)
{
    OSD_setMenuLineColors(selectedMenuLine);
    OSD_writePageIcons(true, '3', true);
    OSD_writeStringAtRow(1, 1, "Preferences");
    OSD_writeStringAtRow(2, 1, "Developer");
    OSD_writeStringAtRow(3, 1, "Firmware version");
}

void handle_MainMenu_Page4(void)
{
    OSD_setMenuLineColors(selectedMenuLine);
    OSD_writePageIcons(true, '4', false);
    OSD_writeStringAtRow(1, 1, "Factory reset");
    OSD_writeStringAtRow(2, 1, "Restart");
    OSD_writeStringAtRow(3, 1, "Language");
    OSD_writeStringAtRow(3, 22, i18nLangName(uiLang));  // "EN-US" / "PT-BR" (never translated)
}

// ====================================================================================
// Factory Reset Confirmation Screen
// ====================================================================================

// External reference to confirmation selection (0 = No selected, 1 = Yes selected)
extern uint8_t factoryResetSelection;

void handle_FactoryResetConfirm(void)
{
    // No row highlighting - this is a special confirmation screen
    OSD_setMenuLineColors(0);

    // Row 1-2: Warning text (no colors)
    OSD_writeStringAtRow(1, 1, "Reset all settings to");
    OSD_writeStringAtRow(2, 1, "factory defaults");

    // Row 3: Yes / No options with selection indicator
    // Format: "     Yes          ->No" or "  ->Yes             No"
    if (factoryResetSelection == 1) {
        // Yes selected
        OSD_writeStringAtRow(3, 8, "Yes", OSD_TEXT_SELECTED);
        OSD_writeStringAtRow(3, 17, " No", OSD_TEXT_NORMAL);
    } else {
        // No selected (default)
        OSD_writeStringAtRow(3, 7, " Yes", OSD_TEXT_NORMAL);
        OSD_writeStringAtRow(3, 18, "No", OSD_TEXT_SELECTED);
    }
}

// ====================================================================================
// Cursor Highlight Handlers
// ====================================================================================

void handle_HighlightRow1(void) { highlightRow(1); }
void handle_HighlightRow2(void) { highlightRow(2); }
void handle_HighlightRow3(void) { highlightRow(3); }
